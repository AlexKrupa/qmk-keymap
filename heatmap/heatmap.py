"""Report key press counts from the ZSA Keymapp heatmap database."""

import argparse
import json
import os
import re
import sqlite3
import sys
from contextlib import closing
from typing import NamedTuple

LAYER_NAMES = ["base", "num", "sym", "nav", "mouse", "sys"]

KEY_COUNT = 52

GRID_WIDTH = 12
HALF_WIDTH = 6

ROW_NAMES = ["unused", "top", "home", "bottom"]

FINGER_BY_COLUMN = [
    "outer", "pinky", "ring", "middle", "index", "index",
    "index", "index", "middle", "ring", "pinky", "outer",
]

_LAYER_PATTERN = re.compile(r"\[(\d+)\]\s*=\s*LAYOUT_voyager\((.*?)\n\)", re.DOTALL)


def parse_layers(source):
    layers = []
    for match in _LAYER_PATTERN.finditer(source):
        tokens = [token.strip() for token in match.group(2).split(",")]
        tokens = [token for token in tokens if token]
        if len(tokens) != KEY_COUNT:
            raise ValueError(
                f"layer {match.group(1)} has {len(tokens)} tokens, expected {KEY_COUNT}"
            )
        layers.append(tokens)

    if len(layers) != len(LAYER_NAMES):
        raise ValueError(f"found {len(layers)} layers, expected {len(LAYER_NAMES)}")

    return layers


class Position(NamedTuple):
    hand: str
    finger: str
    row: str


def keymap_index(heatmap_index):
    """The heatmap numbers each half in turn - `keymap.c` numbers rows across both halves."""
    if heatmap_index < 24:
        return (heatmap_index // HALF_WIDTH) * GRID_WIDTH + heatmap_index % HALF_WIDTH
    if heatmap_index < 26:
        return 24 + heatmap_index
    if heatmap_index < 50:
        offset = heatmap_index - 26
        return (offset // HALF_WIDTH) * GRID_WIDTH + HALF_WIDTH + offset % HALF_WIDTH
    return heatmap_index


def position_attributes(index):
    if index >= 48:
        hand = "left" if index < 50 else "right"
        return Position(hand, "thumb", "thumb")

    column = index % GRID_WIDTH
    hand = "left" if column < HALF_WIDTH else "right"
    return Position(hand, FINGER_BY_COLUMN[column], ROW_NAMES[index // GRID_WIDTH])


def _connect(db_path):
    return sqlite3.connect(f"file:{db_path}?mode=ro", uri=True)


def read_heatmaps(db_path):
    with closing(_connect(db_path)) as connection:
        rows = connection.execute("select revisionId, data from heatmap").fetchall()

    return {revision_id: json.loads(data) for revision_id, data in rows}


def read_revision_dates(db_path):
    with closing(_connect(db_path)) as connection:
        rows = connection.execute("select revisionId, data from revision").fetchall()

    dates = {}
    for revision_id, data in rows:
        revision = json.loads(data)["layout"]["revision"]
        dates[revision_id] = revision.get("createdAt") or ""

    return dates


def newest_revision_id(dates):
    return max(dates, key=lambda revision_id: (dates[revision_id], revision_id))


class Layer(NamedTuple):
    title: str
    codes: list


def _tap_code(key):
    tap = key.get("tap") or {}
    return tap.get("code") or "KC_NO"


def read_revision_layouts(db_path):
    """The layout each revision was recorded with. Its keys are in heatmap order."""
    with closing(_connect(db_path)) as connection:
        rows = connection.execute("select revisionId, data from revision").fetchall()

    layouts = {}
    for revision_id, data in rows:
        layers = json.loads(data)["layout"]["revision"].get("layers")
        if not layers:
            continue

        layouts[revision_id] = [
            Layer(layer.get("title") or "", [_tap_code(key) for key in layer["keys"]])
            for layer in layers
        ]

    return layouts


def layer_name_mismatches(layout):
    """Layer names the revision recorded against the layer order `keymap.c` declares."""
    return [
        (index, LAYER_NAMES[index], layer.title)
        for index, layer in enumerate(layout)
        if layer.title.lower() != LAYER_NAMES[index]
    ]


class Row(NamedTuple):
    layer_index: int
    layer_name: str
    heatmap_index: int
    count: int
    key: str
    hand: str
    finger: str
    row: str


def build_rows(layers, tokens):
    rows = []
    for layer_index, counts in enumerate(layers):
        for heatmap_index, count in enumerate(counts):
            token_index = keymap_index(heatmap_index)
            key = tokens[layer_index][token_index]
            if key == "KC_NO" and count == 0:
                continue

            position = position_attributes(token_index)
            rows.append(Row(
                layer_index,
                LAYER_NAMES[layer_index],
                heatmap_index,
                count,
                key,
                position.hand,
                position.finger,
                position.row,
            ))

    return rows


def totals_by(rows, field):
    totals = {}
    for row in rows:
        value = getattr(row, field)
        totals[value] = totals.get(value, 0) + row.count

    return dict(sorted(totals.items(), key=lambda item: item[1], reverse=True))


def _table(header, lines):
    separator = "| " + " | ".join("---" for _ in header) + " |"
    return ["| " + " | ".join(header) + " |", separator, *lines, ""]


def _totals_table(title, totals):
    total = sum(totals.values()) or 1
    lines = [
        f"| {name} | {count} | {count / total:.1%} |"
        for name, count in totals.items()
    ]
    return [f"## {title}", "", *_table(["name", "count", "pct"], lines)]


def _revision_key(layout, row):
    if layout is None:
        return ""

    return layout[row.layer_index].codes[row.heatmap_index]


def _layout_check(layout):
    out = ["## Layout check", ""]
    if layout is None:
        return out + ["The revision holds no layout. The labels cannot be checked.", ""]

    mismatches = layer_name_mismatches(layout)
    if not mismatches:
        return out + ["The revision layer names match `LAYER_NAMES`.", ""]

    out += [
        "The revision layer order does not match `keymap.c`. Presses that Keymapp recorded before "
        "this keymap was flashed sit on the layers below under the wrong labels. Reset the "
        "heatmap in Keymapp to be sure the counts describe this keymap only.",
        "",
    ]
    lines = [
        f"| {index} | {name} | {title} |" for index, name, title in mismatches
    ]
    return out + _table(["layer", "keymap.c", "revision"], lines)


def render_report(db_path, revision_id, dates, heatmaps, rows, layout=None):
    total = sum(row.count for row in rows)
    out = [
        "# Keymapp heatmap report",
        "",
        f"- Database: `{db_path}`",
        f"- Revision: `{revision_id}`",
        f"- Created: {dates.get(revision_id, '')}",
        f"- Total presses: {total}",
        "",
        "## Revisions in the database",
        "",
    ]
    revision_lines = [
        f"| `{other_id}` | {dates.get(other_id, '')} | "
        f"{sum(sum(counts) for counts in layers)} |"
        for other_id, layers in heatmaps.items()
    ]
    out += _table(["revision", "created", "total"], revision_lines)
    out += _layout_check(layout)

    for layer_index, name in enumerate(LAYER_NAMES):
        layer_rows = sorted(
            (row for row in rows if row.layer_index == layer_index),
            key=lambda row: (-row.count, row.heatmap_index),
        )
        layer_total = sum(row.count for row in layer_rows)
        out += [f"## Layer {layer_index} - {name}", "",
                f"Total presses: {layer_total}", ""]
        lines = [
            f"| {row.heatmap_index} | {row.count} | {row.count / (layer_total or 1):.1%} | "
            f"`{row.key}` | {row.hand} | {row.finger} | {row.row} |"
            for row in layer_rows
        ]
        out += _table(["index", "count", "pct", "key", "hand", "finger", "row"], lines)

    out += _totals_table("Totals per layer", totals_by(rows, "layer_name"))
    out += _totals_table("Totals per hand", totals_by(rows, "hand"))
    out += _totals_table("Totals per finger", totals_by(rows, "finger"))
    out += _totals_table("Totals per row", totals_by(rows, "row"))

    unused = [row for row in rows if row.count == 0 and row.key != "KC_NO"]
    out += ["## Keys with no presses", ""]
    out += _table(
        ["layer", "index", "key"],
        [f"| {row.layer_name} | {row.heatmap_index} | `{row.key}` |" for row in unused],
    )

    stray = [row for row in rows if row.key == "KC_NO" and row.count > 0]
    out += ["## KC_NO with presses", ""]
    out += _table(
        ["layer", "index", "count", "revision key"],
        [
            f"| {row.layer_name} | {row.heatmap_index} | {row.count} | "
            f"`{_revision_key(layout, row)}` |"
            for row in stray
        ],
    )

    return "\n".join(out)


REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_DB = os.path.join(REPO_ROOT, "keymapp.sqlite3")
DEFAULT_KEYMAP = os.path.join(REPO_ROOT, "keyboards/zsa/voyager/keymaps/alexkrupa/keymap.c")


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--db", default=DEFAULT_DB)
    parser.add_argument("--keymap", default=DEFAULT_KEYMAP)
    parser.add_argument("--revision", default=None)
    parser.add_argument("--output", default=None)
    args = parser.parse_args(argv)

    heatmaps = read_heatmaps(args.db)
    dates = read_revision_dates(args.db)
    revision_id = args.revision or newest_revision_id(dates)
    if revision_id not in heatmaps:
        parser.error(f"unknown revision {revision_id}, have {sorted(heatmaps)}")

    with open(args.keymap) as source_file:
        tokens = parse_layers(source_file.read())

    rows = build_rows(heatmaps[revision_id], tokens)
    layout = read_revision_layouts(args.db).get(revision_id)
    report = render_report(args.db, revision_id, dates, heatmaps, rows, layout)

    if args.output:
        with open(args.output, "w") as output_file:
            output_file.write(report + "\n")
    else:
        print(report)

    return 0


if __name__ == "__main__":
    sys.exit(main())
