# Heatmap report

Reads press counts from `keymapp.sqlite3` and labels them from
`keyboards/zsa/voyager/keymaps/alexkrupa/keymap.c`.

```fish
python3 heatmap/heatmap.py                        # newest revision, to stdout
python3 heatmap/heatmap.py --revision orvjZw      # a named revision
python3 heatmap/heatmap.py --output report.md     # to a file
python3 -m unittest discover -s heatmap -v        # tests
```

The database holds one heatmap per Oryx revision. The newest revision has the most data. Older
revisions were recorded with older keymaps. Their labels would be wrong.

## Output format

Markdown. Every section is a `##` heading followed by one table. The headings are stable. A reader
can find a section by its exact text.

| Heading | Columns |
| ------- | ------- |
| `## Revisions in the database` | `revision`, `created`, `total` |
| `## Layout check` | `layer`, `keymap.c`, `revision` |
| `## Layer N - <name>`, one per layer, N is 0 to 5 | `index`, `count`, `pct`, `key`, `hand`, `finger`, `row` |
| `## Totals per layer` | `name`, `count`, `pct` |
| `## Totals per hand` | `name`, `count`, `pct` |
| `## Totals per finger` | `name`, `count`, `pct` |
| `## Totals per row` | `name`, `count`, `pct` |
| `## Keys with no presses` | `layer`, `index`, `key` |
| `## KC_NO with presses` | `layer`, `index`, `count`, `revision key` |

Field values:

- `index` - heatmap position, 0 to 51. Left half 0-25, right half 26-51.
- `count` - press count. `pct` - share of that layer's total, or of the report total in the
  aggregate tables.
- `key` - the token as written in `keymap.c`, in backticks. Aliases such as `HRM_A` are not
  expanded.
- `hand` - `left` or `right`. `finger` - `outer`, `pinky`, `ring`, `middle`, `index` or `thumb`.
  `row` - `top`, `home`, `bottom`, `thumb` or `unused`.

Layer tables are sorted by count, largest first. Above the tables are `- Name: value` lines with the
database path, the revision id, its creation date and the total presses.

`## KC_NO with presses` holds the positions that are empty in `keymap.c` and have presses. Keymapp
reads the Oryx layout, not this repo's `keymap.c`. A position that is a key in Oryx and `KC_NO` here
is in this table. The `revision key` column names the Oryx key, so the source of the presses is
clear. The layer index comes from the keyboard. It follows the `keymap.c` layer order.

## Layout check

The counts are raw: one press total per layer index and key position, with no key codes. Their
meaning depends on the firmware that recorded them. Keymapp keeps one heatmap per Oryx revision and
adds to it even after you flash a build that Oryx does not know. A single heatmap can therefore hold
presses from two layouts, and the schema has no timestamps to separate them.

`## Layout check` compares the layer names in the revision blob against `LAYER_NAMES`. A mismatch
means older presses in the heatmap sit under the wrong labels. The check cannot tell a mixed
heatmap from a clean one, so it warns whenever the two layouts differ. Reset the heatmap in Keymapp
to be sure the counts describe the current keymap only.

Revision `Wv7bYl` shows this: Oryx recorded `BASE, NAV, NUM, SYM, MOUSE, SYS`, and `keymap.c`
declares `base, num, sym, nav, mouse, sys`. Layers 1 to 3 do not match.

## Tests

`heatmap/testdata/keymapp.sqlite3` is a small copy of the Keymapp database, 20 KB against 946 KB. It
holds the `heatmap` and `revision` tables only. The press counts are the real ones. The tests can
check the index map against verified values. Each `revision.data` blob is cut to the one field the
report reads, `createdAt`.

Rebuild it after a new Oryx revision:

```fish
python3 heatmap/testdata/make_fixture.py keymapp.sqlite3
```

## Limits

- A combo press counts once on each key of the combo.
- Counts are per position. A tap and a hold of one key are one count.
- Layer names are a list in `heatmap.py`. A change to the layer order needs a change there.
