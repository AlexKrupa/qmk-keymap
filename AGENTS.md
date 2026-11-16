# CLAUDE.md

This file gives guidance to Claude Code (claude.ai/code) for the code in this repository.

## What this is

QMK keymap for a ZSA Voyager keyboard, using the [external userspace](https://docs.qmk.fm/newbs_external_userspace) pattern. This repo is an overlay. It contains the keymap, community modules and the `heatmap/` report tool, not the QMK firmware itself.

## Build commands

```fish
# Compile
qmk compile -kb zsa/voyager -km alexkrupa

# Compile and flash (then enter bootloader: hold - for layer 5, press top-right key)
qmk flash -kb zsa/voyager -km alexkrupa
```

`make` does not work with external userspace. Always use `qmk compile` / `qmk flash`.

QMK home points to mainline `qmk/qmk_firmware`. This repo is configured as the overlay dir. ZSA-specific features come from community modules (`modules/zsa/`, via `zsa/qmk_modules` submodule).

## Architecture

All keymap source lives in `keyboards/zsa/voyager/keymaps/alexkrupa/`:

- `keymap.c`: the main file with layers, combos, macros, tapping terms, `process_record_user()`, chordal hold layout
- `config.h`: QMK feature flags and timing overrides (tapping term, mouse speed, RGB, combo count)
- `rules.mk`: enables or disables QMK features, for example combos, caps word and Oryx
- `keymap.json`: declares community modules. The keymap layout is in `keymap.c`.
- `i18n.h`: macOS shortcut aliases, for example `KC_MAC_UNDO`

Community modules are declared in `keymap.json` and live in `modules/`. Both `modules/zsa` and `modules/getreuer/custom_shift_keys` are git submodules.

`heatmap/` is a Python tool that reports key press counts from the Keymapp database. See `heatmap/README.md`.

## Key patterns in keymap.c

- `DF_*` aliases use `LT()` for layer-tap, but `process_record_user()` overrides them to emit digit on tap and F-key on hold (numpad layer 2)
- `MCR_ARR` sends `-> ` (arrow macro). `MCR_DLR_BRC` sends `${}` with cursor inside.
- `MAC_DND` and `MAC_LOCK` use the `HSS()`/`HCS()` shorthand macros defined in `config.h`

## Gotchas

- The top row and both outer columns of every layer are `KC_NO` (Voyager is used in 3x5 config, 34 keys with thumbs)
- The `QK_MODS` case in `process_record_user()` fixes modifier handling for mouse and consumer keys on macOS. Do not remove it.
