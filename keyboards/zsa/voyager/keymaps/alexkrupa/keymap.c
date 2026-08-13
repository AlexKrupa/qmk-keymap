#include <stdio.h>
#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "i18n.h"

// -----------------------------------------------------------------------------
// Keycodes
// -----------------------------------------------------------------------------

enum custom_keycodes {
  // Text macros. process_record_user indexes a string table by MCR_ARR offset,
  // so this order must match the table there.
  MCR_ARR = SAFE_RANGE,
  MCR_DLR_BRC,
  MCR_TILDE_SLASH,
  MCR_VQ,
  MCR_VW,
  MCR_VWQ,
  MCR_CODE_FENCE,

  MAC_DND,
  MAC_LOCK,

  // Home row mod tapping-term tuning (SYS layer). FAST = shorter term, SLOW = longer.
  TT_G_FAST, TT_G_SLOW,                          // global (Y / H)
  TT_I_FAST, TT_M_FAST, TT_R_FAST, TT_P_FAST,    // per-finger faster (top row U I O P)
  TT_I_SLOW, TT_M_SLOW, TT_R_SLOW, TT_P_SLOW,    // per-finger slower (home J K L QUO)
  TT_RESET,                                      // zero all (MINUS)
  TT_DUMP,                                       // type effective terms (N)
};

enum keycode_aliases {
  // Dual function keys: number tap, F-key hold.
  // LT layer numbers are arbitrary placeholders - process_record_user overrides both tap and hold.
  NUM_7_F7     = LT(14, KC_W),
  NUM_8_F8     = LT(4, KC_J),
  NUM_9_F9     = LT(13, KC_6),
  NUM_ASTR_F12 = LT(1, KC_F13),

  NUM_1_F1     = LT(6, KC_F6),
  NUM_2_F2     = LT(9, KC_P),
  NUM_3_F3     = LT(14, KC_F21),
  NUM_0_F11    = LT(14, KC_Z),

  NUM_4_F4     = LT(13, KC_P),
  NUM_5_F5     = LT(15, KC_F20),
  NUM_6_F6     = LT(7, KC_K),
  NUM_SLS_F10  = LT(9, KC_T),

  // Home row mods
  HRM_A   = MT(MOD_LGUI, KC_A),
  HRM_S   = MT(MOD_LCTL, KC_S),
  HRM_D   = MT(MOD_LALT, KC_D),
  HRM_F   = MT(MOD_LSFT, KC_F),

  HRM_J   = MT(MOD_RSFT, KC_J),
  HRM_K   = MT(MOD_LALT, KC_K),
  HRM_L   = MT(MOD_RCTL, KC_L),
  HRM_QUO = MT(MOD_RGUI, KC_QUOTE),

  // Bottom row mods
  BRM_Z   = ALL_T(KC_Z),
  BRM_X   = MEH_T(KC_X),
  BRM_C   = MT(MOD_RALT, KC_C),
  BRM_V   = LT(2, KC_V),

  BRM_M   = LT(2, KC_M),
  BRM_COM = MT(MOD_RALT, KC_COMMA),
  BRM_DOT = MEH_T(KC_DOT),
  BRM_SLS = ALL_T(KC_SLASH),
  BRM_ASTR = LT(5, KC_F16),  // KC_ASTR is S(KC_8), too wide for LT(); tap overridden in process_record_user

  // Thumbs
  TMB_BSP = LT(3, KC_BSPC),
  TMB_ESC = LT(1, KC_ESCAPE),
  TMB_ENT = LT(2, KC_ENTER),
  TMB_SPC = LT(4, KC_SPACE),

  // Layer 1 mod-taps: modifier on hold, action on tap
  MT_GUI_SALL = LT(11, KC_F23),  // Left GUI hold / SEL_ALL tap
  MT_ALT_DEL  = LT(10, KC_F24),  // Left Alt hold / MAC_DEL tap
  MT_SFT_CW   = LT(9, KC_F15),   // Left Shift hold / CW_TOGG tap

  // Shortcuts
  CYCLOTAB = LGUI(KC_TAB),
  LAUNCHER = LGUI(KC_SPACE),
  MAC_DEL  = LGUI(KC_BSPC),
  MAC_FIND = LGUI(KC_F),
  MAC_QUIT = LGUI(KC_Q),
  SEL_ALL  = LGUI(KC_A),
  TAB_CLS  = LGUI(KC_W),
  TAB_NXT  = LCTL(KC_TAB),
  TAB_OPN  = LGUI(KC_T),
  TAB_PRV  = LCTL(LSFT(KC_TAB)),
};

// -----------------------------------------------------------------------------
// Layers
// -----------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_voyager(
  KC_NO    , KC_NO , KC_NO , KC_NO , KC_NO   , KC_NO   ,     KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,
  KC_GRAVE , KC_Q  , KC_W  , KC_E  , KC_R    , KC_T    ,     KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_EQUAL,
  KC_TAB   , HRM_A , HRM_S , HRM_D , HRM_F   , KC_G    ,     KC_H    , HRM_J   , HRM_K   , HRM_L   , HRM_QUO , KC_MINUS,
  KC_NO    , BRM_Z , BRM_X , BRM_C , BRM_V   , KC_B    ,     KC_N    , BRM_M   , BRM_COM , BRM_DOT , BRM_SLS , BRM_ASTR,
                                     TMB_BSP , TMB_ESC ,     TMB_ENT , TMB_SPC
),

[1] = LAYOUT_voyager(
  KC_NO , KC_NO       , KC_NO        , KC_NO       , KC_NO         , KC_NO          ,     KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO        , KC_NO,
  KC_NO , KC_NO       , KC_KP_PLUS   , KC_KP_MINUS , KC_KP_EQUAL   , KC_NO          ,     KC_NO    , NUM_7_F7 , NUM_8_F8 , NUM_9_F9 , NUM_ASTR_F12 , KC_NO,
  KC_NO , KC_LEFT_GUI , KC_LEFT_CTRL , KC_LEFT_ALT , KC_LEFT_SHIFT , KC_NO          ,     KC_NO    , NUM_1_F1 , NUM_2_F2 , NUM_3_F3 , NUM_0_F11    , KC_NO,
  KC_NO , KC_NO       , KC_COMMA     , KC_KP_DOT   , KC_COLN       , KC_NO          ,     KC_NO    , NUM_4_F4 , NUM_5_F5 , NUM_6_F6 , NUM_SLS_F10  , KC_NO,
                                                     KC_NO         , KC_TRANSPARENT ,     KC_ENTER , KC_SPACE
),

[2] = LAYOUT_voyager(
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO     , KC_NO       ,     KC_NO    , KC_NO    , KC_NO   , KC_NO       , KC_NO      , KC_NO          ,
  MCR_VQ  , KC_TILD , KC_LABK , KC_RABK , KC_PERC   , MCR_ARR     ,     KC_NO    , KC_LCBR  , KC_RCBR , KC_KP_EQUAL , KC_KP_PLUS , KC_NO          ,
  MCR_VWQ , KC_CIRC , KC_AT   , KC_HASH , KC_DLR    , MCR_DLR_BRC ,     KC_NO    , KC_LPRN  , KC_RPRN , KC_KP_MINUS , KC_GRAVE   , MCR_CODE_FENCE ,
  MCR_VW  , KC_BSLS , KC_PIPE , KC_AMPR , KC_ASTR   , KC_NO       ,     KC_NO    , KC_LBRC  , KC_RBRC , KC_UNDS     , KC_EXLM    , MCR_TILDE_SLASH,
                                          KC_DELETE , KC_TAB      ,     KC_ENTER , KC_SPACE
),

[3] = LAYOUT_voyager(
  KC_NO    , KC_NO       , KC_NO        , KC_NO       , KC_NO          , KC_NO    ,     KC_NO    , KC_NO    , KC_NO , KC_NO    , KC_NO , KC_NO,
  KC_NO    , MAC_QUIT    , TAB_CLS      , TAB_PRV     , TAB_NXT        , TAB_OPN  ,     KC_NO    , KC_NO    , KC_NO , KC_NO    , KC_NO , KC_NO,
  CYCLOTAB , MT_GUI_SALL , KC_LEFT_CTRL , MT_ALT_DEL  , MT_SFT_CW      , MAC_FIND ,     KC_LEFT  , KC_DOWN  , KC_UP , KC_RIGHT , KC_NO , KC_NO,
  KC_NO    , KC_MAC_UNDO , KC_MAC_CUT   , KC_MAC_COPY , KC_MAC_PASTE   , KC_NO    ,     KC_NO    , KC_NO    , KC_NO , KC_NO    , KC_NO , KC_NO,
                                                        KC_TRANSPARENT , KC_NO    ,     KC_ENTER , LAUNCHER
),

[4] = LAYOUT_voyager(
  KC_NO , KC_NO , KC_NO   , KC_NO   , KC_NO   , KC_NO ,     KC_NO , KC_NO          , KC_NO   , KC_NO   , KC_NO        , KC_NO,
  KC_NO , KC_NO , KC_NO   , MS_UP   , KC_NO   , KC_NO ,     KC_NO , MS_BTN4        , MS_WHLU , MS_BTN5 , KC_NO        , KC_NO,
  KC_NO , KC_NO , MS_LEFT , MS_DOWN , MS_RGHT , KC_NO ,     KC_NO , MS_BTN1        , MS_BTN3 , MS_BTN2 , KC_RIGHT_GUI , KC_NO,
  KC_NO , KC_NO , MS_ACL0 , MS_ACL1 , MS_ACL2 , KC_NO ,     KC_NO , MS_WHLL        , MS_WHLD , MS_WHLR , KC_NO        , KC_NO,
                                      KC_NO   , KC_NO ,     KC_NO , KC_TRANSPARENT
),

[5] = LAYOUT_voyager(
  KC_NO  , KC_NO               , KC_NO               , KC_NO             , KC_NO               , KC_NO         ,     KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO                , KC_NO         ,
  KC_NO  , RM_SPDD             , RM_SPDU             , KC_F14            , KC_F15              , KC_NO         ,     TT_G_SLOW , TT_I_SLOW , TT_M_SLOW , TT_R_SLOW , TT_P_SLOW            , QK_BOOT       ,
  KC_NO  , KC_MEDIA_PREV_TRACK , KC_MEDIA_NEXT_TRACK , KC_AUDIO_VOL_DOWN , KC_AUDIO_VOL_UP     , KC_NO         ,     TT_G_FAST , TT_I_FAST , TT_M_FAST , TT_R_FAST , TT_P_FAST            , TT_RESET      ,
  LUMINO , RM_PREV             , RM_NEXT             , RM_HUED           , RM_HUEU             , KC_NO         ,     TT_DUMP   , KC_NO     , MAC_LOCK  , MAC_DND   , KC_MS_JIGGLER_TOGGLE , KC_TRANSPARENT,
                                                                           KC_MEDIA_PLAY_PAUSE , KC_AUDIO_MUTE ,     KC_NO     , KC_NO
)
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  '*', '*', '*', '*'
);

// -----------------------------------------------------------------------------
// Combos
// -----------------------------------------------------------------------------

enum combos {
  SD_TAB,
  SD_CYCLOTAB,
};

const uint16_t PROGMEM combo_sd_tab[] = { HRM_S, HRM_D, COMBO_END};
// Layer 3 S+D positions resolve to these; MT_ALT_DEL is layer-3-only so no collision
const uint16_t PROGMEM combo_sd_cyclotab[] = { KC_LEFT_CTRL, MT_ALT_DEL, COMBO_END};

combo_t key_combos[] = {
  [SD_TAB] = COMBO(combo_sd_tab, KC_TAB),
  [SD_CYCLOTAB] = COMBO(combo_sd_cyclotab, CYCLOTAB),
};

// Tap-only so holding S+D still yields the underlying mods instead of firing the combo
bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
  return combo_index == SD_TAB || combo_index == SD_CYCLOTAB;
}

// -----------------------------------------------------------------------------
// Custom shift keys
// -----------------------------------------------------------------------------

// Custom shift keys: add entries to remap Shift+key behavior.
// Each entry is {key, shifted_key}. Examples:
//   {KC_DOT,  KC_QUES},  // Shift + . = ?
const custom_shift_key_t custom_shift_keys[] = {
  {BRM_COM, KC_SCLN},  // ,;
  {BRM_DOT, KC_COLN},   // .:
  {BRM_ASTR, KC_EXLM}  // *!
};

// -----------------------------------------------------------------------------
// Persisted user config
// -----------------------------------------------------------------------------

// Runtime-adjustable home row mod tapping terms, persisted in the 32-bit keymap
// EEPROM block. Five signed deltas in 10ms-step units (6 bits each, -31..31):
// a global offset added to every HRM, plus one per finger pair (symmetric L/R).
typedef union {
  uint32_t raw;
  struct {
    int32_t global : 6;
    int32_t pinky  : 6;
    int32_t ring   : 6;
    int32_t middle : 6;
    int32_t index  : 6;
  };
} user_config_t;
static user_config_t user_config;

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
}

void eeconfig_init_user(void) {
  user_config.raw = 0;
  eeconfig_update_user(user_config.raw);
}

// -----------------------------------------------------------------------------
// Hold-tap behavior
// -----------------------------------------------------------------------------

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  int16_t term;
  switch (keycode) {
    // Pinky - home
    case HRM_A:
    case HRM_QUO:
        term = TAPPING_TERM + 70 + 10 * (user_config.global + user_config.pinky);
        break;

    // Ring - home
    case HRM_S:
    case HRM_L:
        term = TAPPING_TERM + 40 + 10 * (user_config.global + user_config.ring);
        break;

    // Middle - home
    case HRM_D:
    case HRM_K:
        term = TAPPING_TERM - 10 + 10 * (user_config.global + user_config.middle);
        break;

    // Index - home
    case HRM_F:
    case HRM_J:
        term = TAPPING_TERM - 20 + 10 * (user_config.global + user_config.index);
        break;

    // Pinky - bottom
    case BRM_Z:
    case BRM_SLS:
    case BRM_ASTR:
        term = TAPPING_TERM + 80;
        break;

    // Ring - bottom
    case BRM_X:
    case BRM_DOT:
        term = TAPPING_TERM + 50;
        break;

    // Middle - bottom
    case BRM_C:
    case BRM_COM:
        term = TAPPING_TERM + 20;
        break;

    // Index - bottom
    case BRM_V:
    case BRM_M:
        term = TAPPING_TERM + 10;
        break;

    // Thumbs
    case TMB_BSP:
    case TMB_ESC:
    case TMB_ENT:
    case TMB_SPC:
        term = TAPPING_TERM;
        break;

    default:
        term = TAPPING_TERM;
        break;
  }
  // Terms outside this range aren't practical, and the runtime deltas can reach
  // them - unclamped, an underflow would wrap into a term of ~65 seconds.
  return MIN(MAX(term, 150), 300);
}

#ifdef SPECULATIVE_HOLD
bool get_speculative_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case HRM_F:   // LShift
    case HRM_J:   // RShift
    case HRM_S:   // LCtrl
    case HRM_L:   // RCtrl
    case HRM_D:   // LAlt
    case HRM_K:   // LAlt
    case BRM_C:   // RAlt
    case HRM_A:   // LGui
    case HRM_QUO: // RGui
      return true;
  }
  return false;
}
#endif // SPECULATIVE_HOLD

// Thumbs are '*' in chordal_hold_layout, so chordal hold always permits their
// hold - that exemption is what lets this callback run at all. Safe because
// thumbs rarely roll with the fingers. The layer settles on the next key press,
// with no tapping term wait.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TMB_ESC:
    case TMB_ENT:
      return true;
  }
  return false;
}

#ifdef FLOW_TAP_TERM
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
  if (get_tap_keycode(prev_keycode) < KC_A || get_tap_keycode(prev_keycode) > KC_Z) return 0;
  // Disable flow tap when hotkey modifiers are held (Cmd+A, Ctrl+C, etc.)
  // Excludes Alt so diacritics (Alt+letter) still benefit from flow tap.
  if (get_mods() & MOD_MASK_CG) return 0;

  switch (keycode) {
    // Shift/Alt - fast typing
    case HRM_D:
    case HRM_F:
    case HRM_J:
    case HRM_K:
      return 0;
    // Non-Shift/Alt never used during fast typing
    case HRM_A:
    case HRM_QUO:
    case HRM_S:
    case HRM_L:
    case BRM_Z:
    case BRM_X:
    case BRM_DOT:
    case BRM_SLS:
    case BRM_ASTR:
      return FLOW_TAP_TERM;
    default:
      return 0;
  }
}
#endif // FLOW_TAP_TERM

// -----------------------------------------------------------------------------
// Handlers
// -----------------------------------------------------------------------------

static bool tap_or_hold(keyrecord_t *record, uint16_t tap_kc, uint16_t hold_kc) {
  if (record->tap.count > 0) {
    if (record->event.pressed) {
      register_code16(tap_kc);
    } else {
      unregister_code16(tap_kc);
    }
  } else {
    if (record->event.pressed) {
      register_code16(hold_kc);
    } else {
      unregister_code16(hold_kc);
    }
  }
  return false;
}

// Clamp a tapping-term delta to the 6-bit signed bitfield range.
static int8_t tt_clamp(int8_t v) { return v > 31 ? 31 : (v < -31 ? -31 : v); }

// Adjust one HRM delta by `step` (10ms units), clamp, persist. Embeds `return false`
// like the HSS/HCS macros in config.h - bitfields can't be passed by pointer.
#define TT_ADJUST(field, step)                                  \
  if (record->event.pressed) {                                  \
    user_config.field = tt_clamp(user_config.field + (step));   \
    eeconfig_update_user(user_config.raw);                      \
  }                                                             \
  return false

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QK_MODS ... QK_MODS_MAX:
      // Mouse and consumer keys (volume, media) with modifiers work inconsistently across operating systems,
      // this makes sure that modifiers are always applied to the key that was pressed.
      if (IS_MOUSE_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode)) || IS_CONSUMER_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode))) {
        if (record->event.pressed) {
          add_mods(QK_MODS_GET_MODS(keycode));
          send_keyboard_report();
          wait_ms(2);
          register_code(QK_MODS_GET_BASIC_KEYCODE(keycode));
          return false;
        } else {
          wait_ms(2);
          del_mods(QK_MODS_GET_MODS(keycode));
        }
      }
      break;

    case MCR_ARR ... MCR_CODE_FENCE: {
      // Indexed by keycode - MCR_ARR; order must match the MCR_* enum.
      static const char *const macros[] = {
        "-> ",
        "${}" SS_TAP(X_LEFT),
        "~/",
        ":q" SS_TAP(X_ENTER),
        ":w" SS_TAP(X_ENTER),
        ":wq" SS_TAP(X_ENTER),
        "```" SS_DELAY(25) SS_LSFT(SS_TAP(X_ENTER)) "```" SS_DELAY(25) SS_TAP(X_UP),
      };
      if (record->event.pressed) {
        send_string(macros[keycode - MCR_ARR]);
      }
      return false;
    }

    case MAC_DND:
      HSS(0x9B);
      return false;
    case MAC_LOCK:
      HCS(0x19E);
      return false;

    case NUM_7_F7:     return tap_or_hold(record, KC_7,     KC_F7);
    case NUM_8_F8:     return tap_or_hold(record, KC_8,     KC_F8);
    case NUM_9_F9:     return tap_or_hold(record, KC_9,     KC_F9);
    case NUM_ASTR_F12: return tap_or_hold(record, KC_ASTR,  KC_F12);
    case NUM_1_F1:     return tap_or_hold(record, KC_1,     KC_F1);
    case NUM_2_F2:     return tap_or_hold(record, KC_2,     KC_F2);
    case NUM_3_F3:     return tap_or_hold(record, KC_3,     KC_F3);
    case NUM_0_F11:    return tap_or_hold(record, KC_0,     KC_F11);
    case NUM_4_F4:     return tap_or_hold(record, KC_4,     KC_F4);
    case NUM_5_F5:     return tap_or_hold(record, KC_5,     KC_F5);
    case NUM_6_F6:     return tap_or_hold(record, KC_6,     KC_F6);
    case NUM_SLS_F10:  return tap_or_hold(record, KC_SLASH, KC_F10);

    case MT_GUI_SALL:  return tap_or_hold(record, SEL_ALL,  KC_LEFT_GUI);
    case MT_ALT_DEL:   return tap_or_hold(record, MAC_DEL,  KC_LEFT_ALT);
    // CW_TOGG isn't a basic keycode, so it can't go through tap_or_hold's register_code16
    case MT_SFT_CW:
      if (record->tap.count > 0) {
        if (record->event.pressed) caps_word_toggle();
      } else if (record->event.pressed) {
        register_code(KC_LEFT_SHIFT);
      } else {
        unregister_code(KC_LEFT_SHIFT);
      }
      return false;

    // Override LT tap: KC_F16 placeholder -> KC_ASTR (shifted case handled by custom_shift_keys module)
    case BRM_ASTR:
      if (record->tap.count > 0 && !((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)) {
        if (record->event.pressed) {
          register_code16(KC_ASTR);
        } else {
          unregister_code16(KC_ASTR);
        }
        return false;
      }
      return true;

    // Home row mod tapping-term tuning. FAST shortens (-1 step), SLOW lengthens (+1).
    case TT_G_FAST: TT_ADJUST(global, -1);
    case TT_G_SLOW: TT_ADJUST(global, +1);
    case TT_I_FAST: TT_ADJUST(index,  -1);
    case TT_I_SLOW: TT_ADJUST(index,  +1);
    case TT_M_FAST: TT_ADJUST(middle, -1);
    case TT_M_SLOW: TT_ADJUST(middle, +1);
    case TT_R_FAST: TT_ADJUST(ring,   -1);
    case TT_R_SLOW: TT_ADJUST(ring,   +1);
    case TT_P_FAST: TT_ADJUST(pinky,  -1);
    case TT_P_SLOW: TT_ADJUST(pinky,  +1);

    case TT_RESET:
      if (record->event.pressed) { user_config.raw = 0; eeconfig_update_user(user_config.raw); }
      return false;

    case TT_DUMP:
      // Reuse get_tapping_term so the readout always matches the live terms.
      // It ignores `record` for HRM keys, so NULL is safe.
      if (record->event.pressed) {
        char buf[64];
        snprintf(buf, sizeof(buf), "global=%d index=%d middle=%d ring=%d pinky=%d",
                 10 * user_config.global,
                 get_tapping_term(HRM_F, NULL),
                 get_tapping_term(HRM_D, NULL),
                 get_tapping_term(HRM_S, NULL),
                 get_tapping_term(HRM_A, NULL));
        send_string(buf);
      }
      return false;
  }
  return true;
}
