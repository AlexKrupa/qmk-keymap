# ZSA Voyager QMK keymap

Custom QMK keymap for the ZSA Voyager, using the [external userspace](https://docs.qmk.fm/newbs_external_userspace) pattern. The ZSA firmware repo is cloned separately and never modified; this repo contains only the keymap and community modules.

## Setup

Prerequisites:

```fish
brew install qmk/qmk/qmk
brew install dos2unix
```

Clone ZSA's QMK fork (only needed once):

```fish
qmk setup zsa/qmk_firmware -b firmware25 -H ~/src/oss/qmk_firmware
```

Clone this repo and init submodules:

```fish
git clone <this-repo> ~/src/me/qmk-keymap
cd ~/src/me/qmk-keymap
git submodule update --init --recursive
```

Point QMK at both directories:

```fish
qmk config user.qmk_home=/Users/alexkrupa/src/oss/qmk_firmware
qmk config user.overlay_dir=/Users/alexkrupa/src/me/qmk-keymap
```

The ARM and AVR compilers from Homebrew are keg-only and need to be on PATH. Add to `~/.config/fish/conf.d/qmk.fish`:

```fish
fish_add_path /opt/homebrew/opt/arm-none-eabi-gcc@8/bin
fish_add_path /opt/homebrew/opt/arm-none-eabi-binutils/bin
fish_add_path /opt/homebrew/opt/avr-gcc@8/bin
fish_add_path /opt/homebrew/opt/avr-binutils/bin
```

Verify with `qmk doctor`.

## Usage

Compile:

```fish
qmk compile -kb zsa/voyager -km alexkrupa
```

Compile and flash:

```fish
qmk flash -kb zsa/voyager -km alexkrupa
```

Then enter bootloader mode: hold `-` (activates layer 5) and press the top-right key (`QK_BOOT`). Alternatively, press the physical reset button on the bottom of the left half.

Note: bare `make` does not work with external userspace. Always use `qmk compile` / `qmk flash`.

### Updating the ZSA firmware

```fish
cd ~/src/oss/qmk_firmware
git pull origin firmware25
git submodule update --init --recursive
```

Then rebuild.

## Where to change what

| I want to... | File | What to edit |
|---|---|---|
| Change key positions / layers | `keymap.c` | `keymaps[]` array |
| Add custom shift mappings | `keymap.c` | `custom_shift_keys[]` array |
| Add macros | `keymap.c` | `enum custom_keycodes` + `process_record_user()` |
| Tune tapping term per key | `keymap.c` | `get_tapping_term()` |
| Add/change combos | `keymap.c` | `combo` arrays + `key_combos[]` |
| Enable/disable QMK features | `rules.mk` | e.g. `COMBO_ENABLE = yes` |
| Tune timing, mouse speed, RGB | `config.h` | `#define` overrides |
| Add/remove community modules | `keymap.json` | `"modules"` array |

All keymap files are in `keyboards/zsa/voyager/keymaps/alexkrupa/`.

## Keymap overview

6 layers, QWERTY base. Top row is unused (Voyager 3x6 config).

### Layer 0 - Base

QWERTY with home row mods mirrored on both halves:

- Home row: GUI / Ctrl / Alt / Shift (left), Shift / Alt / Ctrl / GUI (right)
- Bottom row: Hyper(Z) / Meh(X) / AltGr(C) on left, AltGr(,) / Meh(.) / Hyper(/) on right
- Thumbs: Bksp(hold=L1) / Esc(hold=L2) on left, Enter(hold=L3) / Space(hold=L4) on right
- Chordal hold and permissive hold enabled
- Per-key tapping terms: outer columns slower, inner columns faster

### Layer 1 - Nav (hold Bksp)

- Left: app shortcuts (Cmd+Q/W/T/A/F, Cmd+Bksp, undo/cut/copy/paste, tab switching, Caps Word)
- Right: arrows, brackets `(){}[]<>`, colon, `-> ` macro

### Layer 2 - Num (hold Esc)

- Left: `+`, `-`, `=`, `,`, `.`, `:` and bare modifiers
- Right: numpad where tap = digit, hold = F-key (F1-F12), plus `0` and `*`/`/`

### Layer 3 - Sym (hold Enter, or V/M)

- Left: `~ @ # % ^ ! = $ \ | & *` and macros (`-> `, `${}` with cursor inside)
- Right: `! { } = + \` ( ) ' " [ ] - _`

### Layer 4 - Mouse (hold Space)

Mouse movement, buttons (1-5), scroll (all directions), acceleration (0/1/2).

### Layer 5 - Media (hold `-`)

- Left: RGB controls, media prev/next, volume, brightness
- Right: MAC_LOCK, MAC_DND, mouse jiggler toggle, QK_BOOT (top-right)

## Combos

- F + J = Caps Word (`CW_TOGG`)
- Q + W = Tab

## Modules

| Module | Purpose |
|---|---|
| `zsa/oryx` | Keymapp live view and Oryx live training |
| `zsa/mousejiggler` | Mouse jiggler toggle |
| `zsa/defaults` | ZSA default configuration |
| `getreuer/custom_shift_keys` | Custom Shift+key behavior (placeholder, not yet configured) |
