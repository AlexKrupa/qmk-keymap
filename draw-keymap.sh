#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
KEYMAP_C="$SCRIPT_DIR/keyboards/zsa/voyager/keymaps/alexkrupa/keymap.c"
CONFIG="$SCRIPT_DIR/keymap-config.yaml"
OUTPUT_SVG="$SCRIPT_DIR/keymap.svg"

# Use keymap-drawer's own Python (has PyYAML)
PYTHON="$(head -1 "$(which keymap)" | sed 's/^#!//')"

tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT

# 1. Convert keymap.c to JSON
qmk c2json "$KEYMAP_C" --no-cpp > "$tmpdir/keymap.json" 2>/dev/null

# 2. Build tool config (parse_config + draw_config only; combos not valid for -c flag)
$PYTHON -c "
import yaml, sys
cfg = yaml.safe_load(open('$CONFIG'))
cfg.pop('combos', None)
yaml.dump(cfg, sys.stdout, default_flow_style=False, sort_keys=False)
" > "$tmpdir/tool_config.yaml"

# 3. Parse JSON to YAML with custom keycode labels
keymap -c "$tmpdir/tool_config.yaml" parse -q "$tmpdir/keymap.json" \
  -l Base Nav Num Sym Mouse Adjust -c 12 \
  | sed 's/layout_name: LAYOUT_voyager//' \
  > "$tmpdir/parsed.yaml"

# 4. Merge draw_config and combos into parsed keymap
$PYTHON -c "
import yaml, sys
parsed = yaml.safe_load(open('$tmpdir/parsed.yaml'))
config = yaml.safe_load(open('$CONFIG'))
if 'draw_config' in config: parsed['draw_config'] = config['draw_config']
if 'combos' in config: parsed['combos'] = config['combos']
yaml.dump(parsed, sys.stdout, default_flow_style=False, allow_unicode=True, sort_keys=False)
" > "$tmpdir/full.yaml"

# 5. Render SVG
keymap draw "$tmpdir/full.yaml" > "$OUTPUT_SVG"
echo "Generated $OUTPUT_SVG"

if command -v cairosvg &>/dev/null; then
  cairosvg "$OUTPUT_SVG" -o "${OUTPUT_SVG%.svg}.png" -s 2
  echo "Generated ${OUTPUT_SVG%.svg}.png (2x scale)"
fi
