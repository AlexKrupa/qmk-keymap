# Tap-hold stats

Records press durations of tap-hold keys in RAM. A key press types the data as text. An agent
reads the text and suggests tapping terms per key.

## Use

1. Put `THS_DMP` on a key.
2. Type normally for some days.
3. Open a text editor and press `THS_DMP`. The keyboard types the dump. It is blocked until the dump
   ends, 1-3 min for a day of data. Keys pressed during the dump are lost.
4. After `time=`, type the wall-clock time, for example `2026-09-26 14:05`.
5. Save the text to `~/.ai/qmk-keymap/tap-hold-stats/`, one file per dump.

A dump does not clear the data. A reflash, a power cut or an MCU reset clears it.

## Tracked keys

An `MT()` or `LT()` key is tracked when its resolved keycode is the same as its layer 0 keycode.
A key resolved on another layer is not tracked. There are 24 slots, assigned by matrix position in
the order of first press.

## Dump format

```
tap_hold_stats uptime=86400 presses=41230 bucket=10ms under=0-99ms over=350ms
RSFT_T(KC_J) term=180
  alone tap n=812 under=790 10=14 11=5 12=2 13=1
  alone hold n=35 17=1 25=2 over=32
  overlap tap n=2210 under=2150 10=41 11=12 12=5 13=2
  overlap hold n=48 under=3 12=6 13=4 15=2 over=33
time=2026-09-26 14:05
```

- `uptime`: seconds since boot. `presses`: all key presses since boot, tracked or not.
- A key line: the key name and the last term from `get_tapping_term()`, in ms.
- A histogram line: context, decision, total count `n`, then `bucket=count` for each bucket that is
  not zero. Empty histograms are not typed.
- Buckets: `under` is less than 100 ms. `10` to `34` are 10 ms each: `10` is 100-109 ms, `34` is
  340-349 ms. `over` is 350 ms or more.
- Duration: from the raw key press to the raw key release.
- Decision: the decision that QMK made. `tap` or `hold`.
- Context: `overlap` if another key was pressed while this key was down, else `alone`.
- `time`: the wall-clock time that the user typed.

## Key names

Names come from QMK `get_keycode_string()`. Map them to the aliases in the keymap source.

| Keymap source | Dump name |
| --- | --- |
| `MT(MOD_LSFT, KC_F)`, `LSFT_T(KC_F)` | `LSFT_T(KC_F)` |
| `ALL_T(KC_Z)` | `HYPR_T(KC_Z)` |
| `MEH_T(KC_X)` | `MEH_T(KC_X)` |
| `LT(4, KC_SPACE)` | `LT(4,KC_SPC)` |

Short keycode names: `KC_SPC`, `KC_ENT`, `KC_ESC`, `KC_BSPC`, `KC_COMM`, `KC_SLSH`, `KC_QUOT`.

## Which QMK feature decides

The term decides only when the key is still undecided at the end of the term.

| Context | Decided by | Term matters when |
| --- | --- | --- |
| `alone` | Term only | Always. A tap longer than the term is a false hold. |
| `overlap`, same hand | Chordal hold: tap at the other key press | The key was held past the term before the other key press. |
| `overlap`, other hand, other key released first | Permissive hold: hold | Rarely. |
| `overlap`, other hand, this key released first | Term | A roll where this key stays down past the term is a false hold. |
| `overlap`, after a letter within the flow tap term | Flow tap: tap | Never. |
| `overlap`, hold-on-other-key-press keys | Hold at the other key press | Only `alone`. |

Read the keymap source for the per-key settings: `get_tapping_term()`, `get_permissive_hold()`,
`get_hold_on_other_key_press()`, `get_flow_tap_term()`, `chordal_hold_layout`.

## How to read the data

- `alone`: taps and holds form 2 groups. A good term is in the low area between them.
- Taps near the term, on either side, are probable false holds or near misses.
- Holds just above the term in `alone` are probable slow taps.

## Combine dumps

Dumps do not clear the data, so 2 dumps from 1 boot hold the same presses.

1. Boot start = `time` minus `uptime`. The keyboard timer keeps counting while the computer sleeps.
2. Dumps with the same boot start, within about 2 min, are from 1 boot. Use only the latest.
3. Check: no bucket in the latest dump of a boot is smaller than in an earlier dump of that boot.
   If one is smaller, the dumps are from different boots.
4. Add the latest dumps of all boots together. Keep dumps with different `term` values separate.

## Limits

- Presses of the same key with `tap.count > 1` are skipped. These are quick-tap repeats, for
  example a double letter typed within the tapping term.
- Combo presses are not counted. They add to `presses` and can set `overlap` on other keys.
- Time stamps can be 5-15 ms late because of blocking waits in QMK, for example `TAP_CODE_DELAY`.
  QMK decides with the same time stamps, so the data shows what QMK saw.
- A press longer than 65 s goes into a wrong bucket.
- A reconnect of the right half resets the MCU and clears the data.
- A monitor input switch does not cut power to the keyboard.
