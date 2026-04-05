#include QMK_KEYBOARD_H
#include "i18n.h"

enum custom_keycodes {
  MCR_ARR = SAFE_RANGE,
  MCR_DLR_BRC,
  MAC_DND,
  MAC_LOCK,
};

enum keycode_aliases {
  // Dual function keys: number tap, function hold
  DF_7    = LT(14, KC_W),
  DF_8    = LT(4, KC_J),
  DF_9    = LT(13, KC_6),
  DF_ASTR = LT(1, KC_F13),

  DF_1    = LT(6, KC_F6),
  DF_2    = LT(9, KC_P),
  DF_3    = LT(14, KC_F21),
  DF_0    = LT(14, KC_Z),

  DF_4    = LT(13, KC_P),
  DF_5    = LT(15, KC_F20),
  DF_6    = LT(7, KC_K),
  DF_SLS  = LT(9, KC_T),

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
  BRM_V   = LT(3, KC_V),

  BRM_M   = LT(3, KC_M),
  BRM_COM = MT(MOD_RALT, KC_COMMA),
  BRM_DOT = MEH_T(KC_DOT),
  BRM_SLS = ALL_T(KC_SLASH),
  BRM_ASTR = LT(5, KC_F16),  // KC_ASTR is S(KC_8), too wide for LT(); tap overridden in process_record_user

  // Thumbs
  TMB_BSP = LT(1, KC_BSPC),
  TMB_ESC = LT(2, KC_ESCAPE),
  TMB_ENT = LT(3, KC_ENTER),
  TMB_SPC = LT(4, KC_SPACE),

  // Layer 1 mod-taps: modifier on hold, action on tap
  MT_GUI_SA = LT(11, KC_F23),  // Left GUI hold / SEL_ALL tap
  MT_ALT_DL = LT(10, KC_F24),  // Left Alt hold / MAC_DEL tap
  MT_SFT_FD = LT(9, KC_F15),   // Left Shift hold / MAC_FIND tap

  // Shortcuts
  CYCLOTAB = LGUI(KC_TAB),
  MAC_DEL  = LGUI(KC_BSPC),
  MAC_FIND = LGUI(KC_F),
  MAC_QUIT = LGUI(KC_Q),
  SEL_ALL  = LGUI(KC_A),
  TAB_CLS  = LGUI(KC_W),
  TAB_NXT  = LCTL(KC_TAB),
  TAB_OPN  = LGUI(KC_T),
  TAB_PRV  = LCTL(LSFT(KC_TAB)),
};


// Custom shift keys: add entries to remap Shift+key behavior.
// Each entry is {key, shifted_key}. Examples:
//   {KC_DOT,  KC_QUES},  // Shift + . = ?
const custom_shift_key_t custom_shift_keys[] = {
  {BRM_COM, KC_SCLN},  // ,;
  {BRM_DOT, KC_COLN},   // .:
  {BRM_ASTR, KC_EXLM}  // *!
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_voyager(
  KC_NO    , KC_NO , KC_NO , KC_NO , KC_NO   , KC_NO   ,     KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,
  KC_GRAVE , KC_Q  , KC_W  , KC_E  , KC_R    , KC_T    ,     KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_EQUAL,
  KC_TAB   , HRM_A , HRM_S , HRM_D , HRM_F   , KC_G    ,     KC_H    , HRM_J   , HRM_K   , HRM_L   , HRM_QUO , KC_MINUS,
  KC_NO    , BRM_Z , BRM_X , BRM_C , BRM_V   , KC_B    ,     KC_N    , BRM_M   , BRM_COM , BRM_DOT , BRM_SLS , BRM_ASTR,
                                     TMB_BSP , TMB_ESC ,     TMB_ENT , TMB_SPC
),

[1] = LAYOUT_voyager(
  KC_NO    , KC_NO       , KC_NO        , KC_NO       , KC_NO          , KC_NO    ,     KC_NO    , KC_NO    , KC_NO   , KC_NO    , KC_NO   , KC_NO  ,
  KC_NO    , MAC_QUIT    , TAB_CLS      , TAB_PRV     , TAB_NXT        , TAB_OPN  ,     KC_NO    , KC_LPRN  , KC_RPRN , KC_LCBR  , KC_RCBR , KC_NO  ,
  CYCLOTAB , MT_GUI_SA   , KC_LEFT_CTRL , MT_ALT_DL   , MT_SFT_FD      , CW_TOGG  ,     KC_LEFT  , KC_DOWN  , KC_UP   , KC_RIGHT , KC_COLN , MCR_ARR,
  KC_NO    , KC_MAC_UNDO , KC_MAC_CUT   , KC_MAC_COPY , KC_MAC_PASTE   , MAC_FIND ,     KC_NO    , KC_LBRC  , KC_RBRC , KC_LABK  , KC_RABK , KC_NO  ,
                                                        KC_TRANSPARENT , KC_NO    ,     KC_ENTER , KC_SPACE
),

[2] = LAYOUT_voyager(
  KC_NO , KC_NO       , KC_NO        , KC_NO       , KC_NO         , KC_NO          ,     KC_NO , KC_NO    , KC_NO , KC_NO , KC_NO   , KC_NO,
  KC_NO , KC_NO       , KC_PLUS      , KC_MINUS    , KC_EQUAL      , KC_NO          ,     KC_NO , DF_7     , DF_8  , DF_9  , DF_ASTR , KC_NO,
  KC_NO , KC_LEFT_GUI , KC_LEFT_CTRL , KC_LEFT_ALT , KC_LEFT_SHIFT , KC_NO          ,     KC_0  , DF_1     , DF_2  , DF_3  , DF_0    , KC_NO,
  KC_NO , KC_NO       , KC_COMMA     , KC_DOT      , KC_COLN       , KC_NO          ,     KC_NO , DF_4     , DF_5  , DF_6  , DF_SLS  , KC_NO,
                                                     KC_NO         , KC_TRANSPARENT ,     KC_0  , KC_SPACE
),

[3] = LAYOUT_voyager(
  KC_NO , KC_NO   , KC_NO   , KC_NO   , KC_NO     , KC_NO       ,     KC_NO    , KC_NO    , KC_NO   , KC_NO       , KC_NO    , KC_NO,
  KC_NO , KC_TILD , KC_LABK , KC_RABK , KC_PERC   , MCR_ARR     ,     KC_NO    , KC_LCBR  , KC_RCBR , KC_EQUAL    , KC_PLUS  , KC_NO,
  KC_NO , KC_CIRC , KC_AT   , KC_HASH , KC_DLR    , MCR_DLR_BRC ,     KC_NO    , KC_LPRN  , KC_RPRN , KC_KP_MINUS , KC_GRAVE , KC_NO,
  KC_NO , KC_BSLS , KC_PIPE , KC_AMPR , KC_ASTR   , KC_NO       ,     KC_NO    , KC_LBRC  , KC_RBRC , KC_UNDS     , KC_EXLM  , KC_NO,
                                        KC_DELETE , KC_TAB      ,     KC_ENTER , KC_SPACE
),

[4] = LAYOUT_voyager(
  KC_NO , KC_NO , KC_NO   , KC_NO   , KC_NO   , KC_NO ,     KC_NO , KC_NO          , KC_NO   , KC_NO   , KC_NO        , KC_NO,
  KC_NO , KC_NO , KC_NO   , MS_UP   , KC_NO   , KC_NO ,     KC_NO , MS_BTN4        , MS_WHLU , MS_BTN5 , KC_NO        , KC_NO,
  KC_NO , KC_NO , MS_LEFT , MS_DOWN , MS_RGHT , KC_NO ,     KC_NO , MS_BTN1        , MS_BTN3 , MS_BTN2 , KC_RIGHT_GUI , KC_NO,
  KC_NO , KC_NO , MS_ACL0 , MS_ACL1 , MS_ACL2 , KC_NO ,     KC_NO , MS_WHLL        , MS_WHLD , MS_WHLR , KC_NO        , KC_NO,
                                      KC_NO   , KC_NO ,     KC_NO , KC_TRANSPARENT
),

[5] = LAYOUT_voyager(
  KC_NO   , KC_NO               , KC_NO               , KC_NO             , KC_NO               , KC_NO         ,     KC_NO , KC_NO , KC_NO    , KC_NO   , KC_NO                , KC_NO         ,
  RM_NEXT , RM_SPDD             , RM_SPDU             , RM_VALD           , RM_VALU             , KC_NO         ,     KC_NO , KC_NO , KC_NO    , KC_NO   , KC_NO                , QK_BOOT       ,
  RM_PREV , KC_MEDIA_PREV_TRACK , KC_MEDIA_NEXT_TRACK , KC_AUDIO_VOL_DOWN , KC_AUDIO_VOL_UP     , KC_NO         ,     KC_NO , KC_NO , KC_NO    , KC_NO   , KC_NO                , KC_NO         ,
  LUMINO  , RM_SATD             , RM_SATU             , RM_HUED           , RM_HUEU             , KC_NO         ,     KC_NO , KC_NO , MAC_LOCK , MAC_DND , KC_MS_JIGGLER_TOGGLE , KC_TRANSPARENT,
                                                                            KC_MEDIA_PLAY_PAUSE , KC_AUDIO_MUTE ,     KC_NO , KC_NO
)
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  '*', '*', '*', '*'
);

const uint16_t PROGMEM combo0[] = { KC_Q, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_TAB),
};

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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Pinky - home
        case HRM_A:
        case HRM_QUO:
            return TAPPING_TERM + 70;

        // Ring - home
        case HRM_S:
        case HRM_L:
            return TAPPING_TERM + 40;

        // Middle - home
        case HRM_D:
        case HRM_K:
            return TAPPING_TERM - 10;

        // Index - home
        case HRM_F:
        case HRM_J:
            return TAPPING_TERM - 20;

        // Pinky - bottom
        case BRM_Z:
        case BRM_SLS:
        case BRM_ASTR:
            return TAPPING_TERM + 80;

        // Ring - bottom
        case BRM_X:
        case BRM_DOT:
            return TAPPING_TERM + 50;

        // Middle - bottom
        case BRM_C:
        case BRM_COM:
            return TAPPING_TERM + 20;

        // Index - bottom
        case BRM_V:
        case BRM_M:
            return TAPPING_TERM + 10;

        // Thumbs
        case TMB_BSP:
        case TMB_ESC:
        case TMB_ENT:
        case TMB_SPC:
            return TAPPING_TERM;

        default:
            return TAPPING_TERM;
    }
}

#ifdef FLOW_TAP_TERM
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
  if (get_tap_keycode(prev_keycode) < KC_A || get_tap_keycode(prev_keycode) > KC_Z) return 0;
  // Disable flow tap when hotkey modifiers are held (Cmd+A, Ctrl+C, etc.)
  // Excludes Alt so diacritics (Alt+letter) still benefit from flow tap.
  if (get_mods() & MOD_MASK_CG) return 0;
  switch (keycode) {
    // Home row
    case HRM_A:
    case HRM_QUO:
    case HRM_S:
    case HRM_L:

    // Bottom row
    case BRM_Z:
    case BRM_X:
    case BRM_V:
    case BRM_M:
    case BRM_DOT:
    case BRM_SLS:
    case BRM_ASTR:
      return FLOW_TAP_TERM;
    default:
      return 0;
  }
}
#endif // FLOW_TAP_TERM

static bool handle_dual_func(keyrecord_t *record, uint16_t tap_kc, uint16_t hold_kc) {
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
    case MCR_ARR:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_MINUS)SS_DELAY(1)  SS_LSFT(SS_TAP(X_DOT))SS_DELAY(1)  SS_TAP(X_SPACE));
    }
    return false;
    case MCR_DLR_BRC:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_4))SS_DELAY(1)  SS_LSFT(SS_TAP(X_LBRC))SS_DELAY(1)  SS_LSFT(SS_TAP(X_RBRC))SS_DELAY(1)  SS_TAP(X_LEFT));
    }
    return false;
    case MAC_DND:
      HSS(0x9B);
    case MAC_LOCK:
      HCS(0x19E);

    case DF_7:     return handle_dual_func(record, KC_7,     KC_F7);
    case DF_8:     return handle_dual_func(record, KC_8,     KC_F8);
    case DF_9:     return handle_dual_func(record, KC_9,     KC_F9);
    case DF_ASTR:  return handle_dual_func(record, KC_ASTR,  KC_F12);
    case DF_1:     return handle_dual_func(record, KC_1,     KC_F1);
    case DF_2:     return handle_dual_func(record, KC_2,     KC_F2);
    case DF_3:     return handle_dual_func(record, KC_3,     KC_F3);
    case DF_0:     return handle_dual_func(record, KC_0,     KC_F11);
    case DF_4:     return handle_dual_func(record, KC_4,     KC_F4);
    case DF_5:     return handle_dual_func(record, KC_5,     KC_F5);
    case DF_6:     return handle_dual_func(record, KC_6,     KC_F6);
    case DF_SLS:   return handle_dual_func(record, KC_SLASH, KC_F10);

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

    case MT_GUI_SA:
      return handle_dual_func(record, LGUI(KC_A), KC_LEFT_GUI);

    case MT_ALT_DL:
      return handle_dual_func(record, LGUI(KC_BSPC), KC_LEFT_ALT);

    case MT_SFT_FD:
      return handle_dual_func(record, LGUI(KC_F), KC_LEFT_SHIFT);
  }
  return true;
}
