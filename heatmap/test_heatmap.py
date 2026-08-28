import io
import os
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout

import heatmap

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
KEYMAP_PATH = os.path.join(
    REPO_ROOT, "keyboards/zsa/voyager/keymaps/alexkrupa/keymap.c"
)
DB_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)), "testdata/keymapp.sqlite3")


class ParseLayersTest(unittest.TestCase):
    def test_returns_six_layers_of_52_tokens(self):
        with open(KEYMAP_PATH) as source_file:
            layers = heatmap.parse_layers(source_file.read())

        self.assertEqual(6, len(layers))
        for layer in layers:
            self.assertEqual(52, len(layer))

    def test_keeps_tokens_as_written(self):
        with open(KEYMAP_PATH) as source_file:
            layers = heatmap.parse_layers(source_file.read())

        self.assertEqual("KC_NO", layers[0][0])
        self.assertEqual("KC_GRAVE", layers[0][12])
        self.assertEqual("HRM_A", layers[0][25])
        self.assertEqual("TMB_BSP", layers[0][48])
        self.assertEqual("TMB_SPC", layers[0][51])

    def test_ignores_the_chordal_hold_layout(self):
        with open(KEYMAP_PATH) as source_file:
            layers = heatmap.parse_layers(source_file.read())

        self.assertNotIn("'L'", layers[5])


class KeymapIndexTest(unittest.TestCase):
    def test_left_grid(self):
        self.assertEqual(0, heatmap.keymap_index(0))
        self.assertEqual(13, heatmap.keymap_index(7))
        self.assertEqual(25, heatmap.keymap_index(13))

    def test_left_thumbs(self):
        self.assertEqual(48, heatmap.keymap_index(24))
        self.assertEqual(49, heatmap.keymap_index(25))

    def test_right_grid(self):
        self.assertEqual(6, heatmap.keymap_index(26))
        self.assertEqual(18, heatmap.keymap_index(32))
        self.assertEqual(47, heatmap.keymap_index(49))

    def test_right_thumbs(self):
        self.assertEqual(50, heatmap.keymap_index(50))
        self.assertEqual(51, heatmap.keymap_index(51))

    def test_is_a_bijection(self):
        mapped = sorted(heatmap.keymap_index(index) for index in range(52))
        self.assertEqual(list(range(52)), mapped)


class PositionAttributesTest(unittest.TestCase):
    def test_left_home_index_finger(self):
        position = heatmap.position_attributes(heatmap.keymap_index(16))

        self.assertEqual("left", position.hand)
        self.assertEqual("index", position.finger)
        self.assertEqual("home", position.row)

    def test_right_pinky_top(self):
        position = heatmap.position_attributes(heatmap.keymap_index(36))

        self.assertEqual("right", position.hand)
        self.assertEqual("pinky", position.finger)
        self.assertEqual("top", position.row)

    def test_left_thumb(self):
        position = heatmap.position_attributes(48)

        self.assertEqual("left", position.hand)
        self.assertEqual("thumb", position.finger)
        self.assertEqual("thumb", position.row)

    def test_right_thumb(self):
        position = heatmap.position_attributes(51)

        self.assertEqual("right", position.hand)
        self.assertEqual("thumb", position.finger)
        self.assertEqual("thumb", position.row)

    def test_unused_top_row(self):
        position = heatmap.position_attributes(0)

        self.assertEqual("unused", position.row)


class ReadHeatmapsTest(unittest.TestCase):
    def test_reads_six_layers_of_52_counts(self):
        heatmaps = heatmap.read_heatmaps(DB_PATH)

        self.assertIn("Wv7bYl", heatmaps)
        for layers in heatmaps.values():
            self.assertEqual(6, len(layers))
            for counts in layers:
                self.assertEqual(52, len(counts))

    def test_known_totals(self):
        heatmaps = heatmap.read_heatmaps(DB_PATH)

        self.assertEqual(209817, sum(sum(counts) for counts in heatmaps["Wv7bYl"]))
        self.assertEqual(35094, sum(sum(counts) for counts in heatmaps["orvjZw"]))


class RevisionDatesTest(unittest.TestCase):
    def test_reads_a_date_per_revision(self):
        dates = heatmap.read_revision_dates(DB_PATH)

        self.assertEqual(3, len(dates))
        self.assertTrue(all(isinstance(date, str) for date in dates.values()))

    def test_newest_is_the_live_revision(self):
        dates = heatmap.read_revision_dates(DB_PATH)

        self.assertEqual("Wv7bYl", heatmap.newest_revision_id(dates))


class RevisionLayoutsTest(unittest.TestCase):
    def test_reads_six_layers_of_52_codes(self):
        layout = heatmap.read_revision_layouts(DB_PATH)["Wv7bYl"]

        self.assertEqual(6, len(layout))
        for layer in layout:
            self.assertEqual(52, len(layer.codes))

    def test_keys_are_in_heatmap_order(self):
        layout = heatmap.read_revision_layouts(DB_PATH)["Wv7bYl"]

        self.assertEqual("KC_Y", layout[0].codes[32])
        self.assertEqual("KC_SPACE", layout[0].codes[51])

    def test_reports_the_swapped_layer_order(self):
        layout = heatmap.read_revision_layouts(DB_PATH)["Wv7bYl"]

        self.assertEqual(
            [(1, "num", "NAV"), (2, "sym", "NUM"), (3, "nav", "SYM")],
            heatmap.layer_name_mismatches(layout),
        )


class BuildRowsTest(unittest.TestCase):
    def setUp(self):
        with open(KEYMAP_PATH) as source_file:
            self.tokens = heatmap.parse_layers(source_file.read())
        self.layers = heatmap.read_heatmaps(DB_PATH)["orvjZw"]
        self.rows = heatmap.build_rows(self.layers, self.tokens)

    def test_index_map_matches_known_counts(self):
        base = {row.heatmap_index: row for row in self.rows if row.layer_index == 0}

        self.assertEqual(("KC_Q", 26), (base[7].key, base[7].count))
        self.assertEqual(("KC_Y", 531), (base[32].key, base[32].count))
        self.assertEqual(("TMB_SPC", 2918), (base[51].key, base[51].count))

    def test_drops_unused_positions(self):
        self.assertFalse(
            any(row.key == "KC_NO" and row.count == 0 for row in self.rows)
        )

    def test_keeps_every_press(self):
        raw_total = sum(sum(counts) for counts in self.layers)

        self.assertEqual(raw_total, sum(row.count for row in self.rows))

    def test_layer_names(self):
        self.assertEqual("base", self.rows[0].layer_name)
        self.assertEqual({"base", "num", "sym", "nav", "mouse", "sys"},
                         {row.layer_name for row in self.rows})


class TotalsByTest(unittest.TestCase):
    def test_sums_by_field_and_sorts_by_count(self):
        rows = [
            heatmap.Row(0, "base", 7, 10, "KC_Q", "left", "pinky", "top"),
            heatmap.Row(0, "base", 8, 30, "KC_W", "left", "ring", "top"),
            heatmap.Row(0, "base", 32, 5, "KC_Y", "right", "index", "top"),
        ]

        self.assertEqual({"left": 40, "right": 5}, heatmap.totals_by(rows, "hand"))
        self.assertEqual(["ring", "pinky", "index"], list(heatmap.totals_by(rows, "finger")))


class RenderReportTest(unittest.TestCase):
    def setUp(self):
        with open(KEYMAP_PATH) as source_file:
            tokens = heatmap.parse_layers(source_file.read())
        self.heatmaps = heatmap.read_heatmaps(DB_PATH)
        self.dates = heatmap.read_revision_dates(DB_PATH)
        rows = heatmap.build_rows(self.heatmaps["Wv7bYl"], tokens)
        self.layout = heatmap.read_revision_layouts(DB_PATH)["Wv7bYl"]
        self.report = heatmap.render_report(
            DB_PATH, "Wv7bYl", self.dates, self.heatmaps, rows, self.layout
        )

    def test_header_names_the_revision_and_total(self):
        self.assertIn("Wv7bYl", self.report)
        self.assertIn("209817", self.report)

    def test_lists_every_revision(self):
        for revision_id in self.heatmaps:
            self.assertIn(revision_id, self.report)

    def test_has_a_section_per_layer(self):
        for layer_index, name in enumerate(heatmap.LAYER_NAMES):
            self.assertIn(f"## Layer {layer_index} - {name}", self.report)

    def test_layer_rows_are_sorted_by_count(self):
        section = self.report.split("## Layer 0")[1].split("## Layer 1")[0]
        counts = [
            int(line.split("|")[2].strip())
            for line in section.splitlines()
            if line.startswith("| ") and line.split("|")[1].strip().isdigit()
        ]

        self.assertEqual(sorted(counts, reverse=True), counts)

    def test_has_aggregates_and_checks(self):
        self.assertIn("## Totals per hand", self.report)
        self.assertIn("## Totals per finger", self.report)
        self.assertIn("## Totals per row", self.report)
        self.assertIn("## Totals per layer", self.report)
        self.assertIn("## Keys with no presses", self.report)
        self.assertIn("## KC_NO with presses", self.report)
        self.assertIn("## Layout check", self.report)

    def test_layout_check_warns_about_the_swapped_layers(self):
        section = self.report.split("## Layout check")[1].split("## Layer 0")[0]

        self.assertIn("does not match `keymap.c`", section)
        self.assertIn("| 3 | nav | SYM |", section)

    def test_stray_presses_name_the_revision_key(self):
        section = self.report.split("## KC_NO with presses")[1]

        self.assertIn("revision key", section)
        self.assertIn("| num | 38 | 964 | `KC_LEFT` |", section)


class MainTest(unittest.TestCase):
    def run_main(self, extra_argv):
        return heatmap.main(["--db", DB_PATH, "--keymap", KEYMAP_PATH, *extra_argv])

    def test_prints_the_newest_revision_by_default(self):
        buffer = io.StringIO()
        with redirect_stdout(buffer):
            exit_code = self.run_main([])

        self.assertEqual(0, exit_code)
        self.assertIn("Wv7bYl", buffer.getvalue())
        self.assertIn("209817", buffer.getvalue())

    def test_selects_a_revision(self):
        buffer = io.StringIO()
        with redirect_stdout(buffer):
            self.run_main(["--revision", "orvjZw"])

        self.assertIn("Revision: `orvjZw`", buffer.getvalue())
        self.assertIn("Total presses: 35094", buffer.getvalue())

    def test_writes_a_file(self):
        with tempfile.TemporaryDirectory() as directory:
            path = os.path.join(directory, "report.md")
            self.run_main(["--output", path])

            with open(path) as report_file:
                self.assertIn("# Keymapp heatmap report", report_file.read())

    def test_rejects_an_unknown_revision(self):
        with redirect_stderr(io.StringIO()), self.assertRaises(SystemExit):
            self.run_main(["--revision", "nope"])


if __name__ == "__main__":
    unittest.main()
