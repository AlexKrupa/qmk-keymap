# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

QMK keymap for a ZSA Voyager keyboard, using the [external userspace](https://docs.qmk.fm/newbs_external_userspace) pattern. This repo is an overlay - it contains the keymap, community modules and the `heatmap/` report tool, not the QMK firmware itself.

## Build commands

```fish
# Compile
qmk compile -kb zsa/voyager -km alexkrupa

# Compile and flash (then enter bootloader: hold - for layer 5, press top-right key)
qmk flash -kb zsa/voyager -km alexkrupa
```

`make` does not work with external userspace - always use `qmk compile` / `qmk flash`.

QMK home points to mainline `qmk/qmk_firmware`. This repo is configured as the overlay dir. ZSA-specific features come from community modules (`modules/zsa/`, via `zsa/qmk_modules` submodule).

## Architecture

All keymap source lives in `keyboards/zsa/voyager/keymaps/alexkrupa/`:

- `keymap.c` - the main file: layers, combos, macros, tapping terms, `process_record_user()`, chordal hold layout
- `config.h` - QMK feature flags and timing overrides (tapping term, mouse speed, RGB, combo count)
- `rules.mk` - enables/disables QMK features (combos, caps word, oryx, etc.)
- `keymap.json` - declares community modules (not the keymap layout - that's in `keymap.c`)
- `i18n.h` - macOS shortcut aliases (`KC_MAC_UNDO`, etc.)

Community modules are declared in `keymap.json` and live in `modules/`. Both `modules/zsa` and `modules/getreuer/custom_shift_keys` are git submodules.

`heatmap/` is a Python tool that reports key press counts from the Keymapp database. See `heatmap/README.md`.

## Key patterns in keymap.c

- `DF_*` aliases use `LT()` for layer-tap, but `process_record_user()` overrides them to emit digit on tap and F-key on hold (numpad layer 2)
- `MCR_ARR` sends `-> ` (arrow macro). `MCR_DLR_BRC` sends `${}` with cursor inside.
- `MAC_DND` and `MAC_LOCK` use the `HSS()`/`HCS()` shorthand macros defined in `config.h`

## Gotchas

- The top row of every layer is `KC_NO` (Voyager is used in 3x6 config, ignoring the top physical row)
- The `QK_MODS` case in `process_record_user()` fixes modifier handling for mouse/consumer keys on macOS - don't remove it
