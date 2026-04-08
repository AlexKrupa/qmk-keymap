# ZSA Voyager QMK keymap

Custom QMK keymap for the ZSA Voyager, using the
[external userspace](https://docs.qmk.fm/newbs_external_userspace) pattern. Uses mainline QMK
firmware (not [ZSA's fork](https://github.com/zsa/qmk_firmware)) with ZSA-specific features pulled
in as [community modules](https://github.com/zsa/qmk_modules). The firmware repo is cloned
separately and never modified; this repo contains only the keymap and community modules.

## Overview

![Keymap](keymap.svg)

6 layers, QWERTY base. The Voyager has 4 rows and 6 columns per half; this keymap uses 3 rows (top
row unused) and 5 columns, plus an outer 6th column for `` ` ``, `=`, Tab, `-`, and RGB controls on
layer 5. With both thumb clusters that's 40 keys total (36 main + 4 thumbs).

Layers:

- **BASE** - letters, home-row mods, bottom-row mods. Thumbs hold into the other layers.
- **NAV** - arrows, macOS app/tab shortcuts, clipboard, brackets.
- **NUM** - operators and modifiers on the left, numpad on the right where hold = F1-F12.
- **SYM** - symbols for typing code, plus vim (`:w`, `:wq`, `:q!`), markdown code fence, and `~/`
  macros.
- **MOUSE** - pointer, buttons, scroll.
- **SYS** - RGB, volume, brightness, media, lock, DND, jiggler, bootloader.

RGB uses [Lumino](https://getreuer.info/posts/keyboards/lumino/) for brightness and
[PaletteFx](https://getreuer.info/posts/keyboards/palettefx/) for effects and palettes.

## Setup

Prerequisites:

```fish
brew install qmk/qmk/qmk
brew install dos2unix
```

Clone mainline QMK firmware and init its submodules:

```fish
qmk setup -H ~/<path-to>/qmk-firmware
cd ~/<path-to>/qmk-firmware
make git-submodule
```

Clone this repo with submodules:

```fish
git clone --recurse-submodules <this-repo> ~/<path-to>/qmk-keymap
```

Or if already cloned:

```fish
cd ~/<path-to>/qmk-keymap
git submodule update --init --recursive
```

Point QMK at both directories (config at `~/Library/Application Support/qmk/qmk.ini` on macOS).

```fish
qmk config user.qmk_home=~/<path-to>/qmk-firmware
qmk config user.overlay_dir=~/<path-to>/qmk-keymap
```

Homebrew's ARM and AVR compilers aren't on PATH by default:

```fish
fish_add_path /opt/homebrew/opt/arm-none-eabi-gcc@8/bin
fish_add_path /opt/homebrew/opt/arm-none-eabi-binutils/bin
fish_add_path /opt/homebrew/opt/avr-gcc@8/bin
fish_add_path /opt/homebrew/opt/avr-binutils/bin
```

Verify with `qmk doctor`.

## Usage

Bare `make` does not work with external userspace. Always use `qmk compile` / `qmk flash`.

Compile (add `--compiledb` to generate `compile_commands.json` for LSP cross-file navigation):

```fish
qmk compile -kb zsa/voyager -km alexkrupa
```

Compile and flash:

```fish
qmk flash -kb zsa/voyager -km alexkrupa
```

Then enter bootloader mode: press the physical reset button on the bottom of the left half.
Alternatively, hold `*` (activates layer 5) and press the top-right key (`QK_BOOT`).

### Updating QMK firmware

```fish
cd ~/<path-to>/qmk-firmware
git pull
make git-submodule
```

Then rebuild.

## Where to change what

| I want to...                  | File          | What to edit                                     |
| ----------------------------- | ------------- | ------------------------------------------------ |
| Change key positions / layers | `keymap.c`    | `keymaps[]` array                                |
| Add custom shift mappings     | `keymap.c`    | `custom_shift_keys[]` array                      |
| Add macros                    | `keymap.c`    | `enum custom_keycodes` + `process_record_user()` |
| Tune tapping term per key     | `keymap.c`    | `get_tapping_term()`                             |
| Add/change combos             | `keymap.c`    | `combo` arrays + `key_combos[]`                  |
| Enable/disable QMK features   | `rules.mk`    | e.g. `COMBO_ENABLE = yes`                        |
| Tune timing, mouse speed, RGB | `config.h`    | `#define` overrides                              |
| Add/remove community modules  | `keymap.json` | `"modules"` array                                |

All keymap files are in `keyboards/zsa/voyager/keymaps/alexkrupa/`.

## Modules

| Module                       | Purpose                                            |
| ---------------------------- | -------------------------------------------------- |
| `zsa/oryx`                   | Keymapp live view and Oryx live training           |
| `zsa/mousejiggler`           | Mouse jiggler toggle                               |
| `getreuer/cyclotab`          | Cmd+Tab cycling that auto-releases on layer change |
| `getreuer/custom_shift_keys` | Custom Shift+key behavior (`,;` `.:` `*!`)         |
| `getreuer/lumino`            | Brightness cycling (0 / 40 / 100%)                 |
| `getreuer/palettefx`         | RGB effects and palettes                           |

## Resources

- [Pascal Getreuer](https://getreuer.info/posts/keyboards/faqs/index.html) and his
  [QMK keymap repo](https://github.com/getreuer/qmk-keymap) - a goldmine of ideas
- [precondition's home row mods guide](https://precondition.github.io/home-row-mods) - the best
  intro to the topic
- [urob's timeless home row mods](https://github.com/urob/zmk-config#timeless-homerow-mods) - the
  standard for home row mod timing
- [sunaku's Glove80 keymap](https://sunaku.github.io/moergo-glove80-keyboard.html) - a deep dive
  into layers, combos and philosophy that got me down this rabbit hole, even though I don't really
  use the Glove80 anymore
- [Moosy's TailorKey](https://sites.google.com/view/tailorkey/) - sunaku's ideas made approachable
- [r/ErgoMechKeyboards](https://reddit.com/r/ErgoMechKeyboards) - a steady stream of ideas and
  discussion
