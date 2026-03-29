#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
  ST_MACRO_2,
  MAC_DND,
  MAC_LOCK,
};

// Custom shift keys: add entries to remap Shift+key behavior.
// Each entry is {key, shifted_key}. Examples:
//   {KC_DOT,  KC_QUES},  // Shift + . = ?
//   {KC_COMM, KC_EXLM},  // Shift + , = !
//   {KC_MINS, KC_EQL},   // Shift + - = =
// const custom_shift_key_t custom_shift_keys[] = {};

#define DUAL_FUNC_0 LT(14, KC_W)
#define DUAL_FUNC_1 LT(4, KC_J)
#define DUAL_FUNC_2 LT(13, KC_6)
#define DUAL_FUNC_3 LT(1, KC_F13)
#define DUAL_FUNC_4 LT(6, KC_F6)
#define DUAL_FUNC_5 LT(9, KC_P)
#define DUAL_FUNC_6 LT(14, KC_F21)
#define DUAL_FUNC_7 LT(14, KC_Z)
#define DUAL_FUNC_8 LT(13, KC_P)
#define DUAL_FUNC_9 LT(15, KC_F20)
#define DUAL_FUNC_10 LT(7, KC_K)
#define DUAL_FUNC_11 LT(9, KC_T)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_GRAVE,       KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_EQUAL,
    KC_TAB,         MT(MOD_LGUI, KC_A),MT(MOD_LCTL, KC_S),MT(MOD_LALT, KC_D),MT(MOD_LSFT, KC_F),KC_G,                                           KC_H,           MT(MOD_RSFT, KC_J),MT(MOD_LALT, KC_K),MT(MOD_RCTL, KC_L),MT(MOD_RGUI, KC_SCLN),KC_QUOTE,
    KC_UNDS,        ALL_T(KC_Z),    MEH_T(KC_X),    MT(MOD_RALT, KC_C),LT(3, KC_V),    KC_B,                                           KC_N,           LT(3, KC_M),    MT(MOD_RALT, KC_COMMA),MEH_T(KC_DOT),  ALL_T(KC_SLASH),LT(5, KC_MINUS),
                                                    LT(1, KC_BSPC), LT(2, KC_ESCAPE),                                LT(3, KC_ENTER),LT(4, KC_SPACE)
  ),
  [1] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    LGUI(KC_TAB),   LGUI(KC_Q),     LGUI(KC_W),     LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),   LGUI(KC_T),                                     KC_NO,          KC_LPRN,        KC_RPRN,        KC_LCBR,        KC_RCBR,        KC_NO,
    LGUI(KC_A),     KC_LEFT_GUI,    KC_LEFT_CTRL,   KC_LEFT_ALT,    KC_LEFT_SHIFT,  CW_TOGG,                                        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_COLN,        ST_MACRO_0,
    LGUI(KC_BSPC),  KC_MAC_UNDO,    KC_MAC_CUT,     KC_MAC_COPY,    KC_MAC_PASTE,   LGUI(KC_F),                                     KC_NO,          KC_LBRC,        KC_RBRC,        KC_LABK,        KC_RABK,        KC_NO,
                                                    KC_TRANSPARENT, KC_NO,                                          KC_ENTER,       KC_SPACE
  ),
  [2] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_PLUS,        KC_MINUS,       KC_EQUAL,       KC_NO,                                          KC_NO,          DUAL_FUNC_0,    DUAL_FUNC_1,    DUAL_FUNC_2,    DUAL_FUNC_3,    KC_NO,
    KC_NO,          KC_LEFT_GUI,    KC_LEFT_CTRL,   KC_LEFT_ALT,    KC_LEFT_SHIFT,  KC_NO,                                          KC_0,           DUAL_FUNC_4,    DUAL_FUNC_5,    DUAL_FUNC_6,    DUAL_FUNC_7,    KC_NO,
    KC_NO,          KC_NO,          KC_COMMA,       KC_DOT,         KC_COLN,        KC_NO,                                          KC_NO,          DUAL_FUNC_8,    DUAL_FUNC_9,    DUAL_FUNC_10,   DUAL_FUNC_11,   KC_NO,
                                                    KC_NO,          KC_TRANSPARENT,                                 KC_0,           KC_SPACE
  ),
  [3] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_TILD,        KC_AT,          KC_HASH,        KC_PERC,        ST_MACRO_1,                                     KC_EXLM,        KC_LCBR,        KC_RCBR,        KC_EQUAL,       KC_PLUS,        KC_NO,
    KC_NO,          KC_CIRC,        KC_EXLM,        KC_EQUAL,       KC_DLR,         ST_MACRO_2,                                     KC_GRAVE,       KC_LPRN,        KC_RPRN,        KC_QUOTE,       KC_DQUO,        KC_NO,
    KC_NO,          KC_BSLS,        KC_PIPE,        KC_AMPR,        KC_ASTR,        KC_NO,                                          KC_NO,          KC_LBRC,        KC_RBRC,        KC_KP_MINUS,    KC_UNDS,        KC_NO,
                                                    KC_DELETE,      KC_TAB,                                         KC_TRANSPARENT, KC_SPACE
  ),
  [4] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_MS_UP,       KC_NO,          KC_NO,                                          KC_NO,          KC_MS_BTN4,     KC_MS_WH_UP,    KC_MS_BTN5,     KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_NO,                                          KC_NO,          KC_MS_BTN1,     KC_MS_BTN3,     KC_MS_BTN2,     KC_RIGHT_GUI,   KC_NO,
    KC_NO,          KC_NO,          KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   KC_NO,                                          KC_NO,          KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_RIGHT, KC_NO,          KC_NO,
                                                    KC_NO,          KC_NO,                                          KC_NO,          KC_TRANSPARENT
  ),
  [5] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    RGB_MODE_FORWARD,RGB_SPD,        RGB_SPI,        RGB_VAD,        RGB_VAI,        KC_BRIGHTNESS_UP,                                KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          QK_BOOT,
    RGB_SLD,        KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_BRIGHTNESS_DOWN,                                KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    RGB_TOG,        RGB_SAD,        RGB_SAI,        RGB_HUD,        RGB_HUI,        KC_NO,                                          KC_NO,          KC_NO,          MAC_LOCK,       MAC_DND,        KC_MS_JIGGLER_TOGGLE,KC_TRANSPARENT,
                                                    KC_MEDIA_PLAY_PAUSE,KC_AUDIO_MUTE,                                  KC_NO,          KC_NO
  ),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  '*', '*', '*', '*'
);

const uint16_t PROGMEM combo0[] = { MT(MOD_LSFT, KC_F), MT(MOD_RSFT, KC_J), COMBO_END};
const uint16_t PROGMEM combo1[] = { KC_Q, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, CW_TOGG),
    COMBO(combo1, KC_TAB),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LGUI, KC_A):
            return TAPPING_TERM + 60;
        case MT(MOD_LCTL, KC_S):
            return TAPPING_TERM + 20;
        case MT(MOD_LALT, KC_D):
            return TAPPING_TERM -10;
        case MT(MOD_LSFT, KC_F):
            return TAPPING_TERM -20;
        case ALL_T(KC_Z):
            return TAPPING_TERM + 60;
        case MEH_T(KC_X):
            return TAPPING_TERM + 20;
        case MT(MOD_RSFT, KC_J):
            return TAPPING_TERM -20;
        case MT(MOD_LALT, KC_K):
            return TAPPING_TERM -10;
        case MT(MOD_RCTL, KC_L):
            return TAPPING_TERM + 20;
        case MT(MOD_RGUI, KC_SCLN):
            return TAPPING_TERM + 60;
        case MEH_T(KC_DOT):
            return TAPPING_TERM + 20;
        case ALL_T(KC_SLASH):
            return TAPPING_TERM + 60;
        case LT(5, KC_MINUS):
            return TAPPING_TERM + 80;
        default:
            return TAPPING_TERM;
    }
}






static bool handle_dual_func(keyrecord_t *record,
                             uint16_t tap_kc, uint16_t hold_kc) {
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
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_MINUS)SS_DELAY(1)  SS_LSFT(SS_TAP(X_DOT))SS_DELAY(1)  SS_TAP(X_SPACE));
    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_MINUS)SS_DELAY(1)  SS_LSFT(SS_TAP(X_DOT))SS_DELAY(1)  SS_TAP(X_SPACE));
    }
    break;
    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_4))SS_DELAY(1)  SS_LSFT(SS_TAP(X_LBRC))SS_DELAY(1)  SS_LSFT(SS_TAP(X_RBRC))SS_DELAY(1)  SS_TAP(X_LEFT));
    }
    break;
    case MAC_DND:
      HSS(0x9B);
    case MAC_LOCK:
      HCS(0x19E);

    case DUAL_FUNC_0:  return handle_dual_func(record, KC_7,     KC_F7);
    case DUAL_FUNC_1:  return handle_dual_func(record, KC_8,     KC_F8);
    case DUAL_FUNC_2:  return handle_dual_func(record, KC_9,     KC_F9);
    case DUAL_FUNC_3:  return handle_dual_func(record, KC_ASTR,  KC_F12);
    case DUAL_FUNC_4:  return handle_dual_func(record, KC_1,     KC_F1);
    case DUAL_FUNC_5:  return handle_dual_func(record, KC_2,     KC_F2);
    case DUAL_FUNC_6:  return handle_dual_func(record, KC_3,     KC_F3);
    case DUAL_FUNC_7:  return handle_dual_func(record, KC_0,     KC_F11);
    case DUAL_FUNC_8:  return handle_dual_func(record, KC_4,     KC_F4);
    case DUAL_FUNC_9:  return handle_dual_func(record, KC_5,     KC_F5);
    case DUAL_FUNC_10: return handle_dual_func(record, KC_6,     KC_F6);
    case DUAL_FUNC_11: return handle_dual_func(record, KC_SLASH, KC_F10);
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}
