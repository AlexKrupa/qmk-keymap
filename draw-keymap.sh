#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
KEYMAP_C="$SCRIPT_DIR/keyboards/zsa/voyager/keymaps/alexkrupa/keymap.c"
CONFIG="$SCRIPT_DIR/keymap-config.yaml"
COMBOS="$SCRIPT_DIR/combos.yaml"
LAYOUT_JSON="$SCRIPT_DIR/voyager-3x6.json"
OUTPUT_SVG="$SCRIPT_DIR/keymap.svg"

# Use keymap-drawer's own Python (has PyYAML)
PYTHON="$(head -1 "$(which keymap)" | sed 's/^#!//')"

tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT

# 1. Convert keymap.c to JSON
qmk c2json "$KEYMAP_C" --no-cpp > "$tmpdir/keymap.json" 2>/dev/null

# 2. Parse JSON to YAML with custom keycode labels
keymap -c "$CONFIG" parse -q "$tmpdir/keymap.json" \
  -l BASE NUM SYM NAV MOUSE SYSTEM -c 12 \
  | sed '/layout_name: LAYOUT_voyager/d' \
  > "$tmpdir/parsed.yaml"

# 3. Strip top row (Voyager used in 3x6 config, top row is KC_NO)
$PYTHON -c "
import yaml, sys

parsed = yaml.safe_load(open('$tmpdir/parsed.yaml'))
for name, rows in parsed.get('layers', {}).items():
    if isinstance(rows, list) and isinstance(rows[0], list):
        parsed['layers'][name] = rows[1:]
yaml.dump(parsed, sys.stdout, default_flow_style=False, allow_unicode=True, sort_keys=False)
" > "$tmpdir/stripped.yaml"

# 4. Render SVG (layout JSON via -j, combos merged from second YAML)
keymap -c "$CONFIG" draw -j "$LAYOUT_JSON" "$tmpdir/stripped.yaml" "$COMBOS" > "$OUTPUT_SVG"
echo "Generated $OUTPUT_SVG"

if command -v cairosvg &>/dev/null; then
  cairosvg "$OUTPUT_SVG" -o "${OUTPUT_SVG%.svg}.png" -s 2
  echo "Generated ${OUTPUT_SVG%.svg}.png (2x scale)"
fi
