#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  MCR_ARR,
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
  BRM_ASTR = LT(5, KC_ASTR),

  // Thumbs
  TMB_BSP = LT(1, KC_BSPC),
  TMB_ESC = LT(2, KC_ESCAPE),
  TMB_ENT = LT(3, KC_ENTER),
  TMB_SPC = LT(4, KC_SPACE),

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
  {KC_ASTR, KC_EXLM}   // *!
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌─────┬───────┬───────┬───────┬─────────┬─────────┐   ┌─────────┬─────────┬─────────┬─────────┬─────────┬──────────┐
//    │ no  │  no   │  no   │  no   │   no    │   no    │   │   no    │   no    │   no    │   no    │   no    │    no    │
//    ├─────┼───────┼───────┼───────┼─────────┼─────────┤   ├─────────┼─────────┼─────────┼─────────┼─────────┼──────────┤
//    │  `  │   q   │   w   │   e   │    r    │    t    │   │    y    │    u    │    i    │    o    │    p    │    =     │
//    ├─────┼───────┼───────┼───────┼─────────┼─────────┤   ├─────────┼─────────┼─────────┼─────────┼─────────┼──────────┤
//    │ tab │ HRM_A │ HRM_S │ HRM_D │  HRM_F  │    g    │   │    h    │  HRM_J  │  HRM_K  │  HRM_L  │ HRM_QUO │    -     │
//    ├─────┼───────┼───────┼───────┼─────────┼─────────┤   ├─────────┼─────────┼─────────┼─────────┼─────────┼──────────┤
//    │ no  │ BRM_Z │ BRM_X │ BRM_C │  BRM_V  │    b    │   │    n    │  BRM_M  │ BRM_COM │ BRM_DOT │ BRM_SLS │ BRM_ASTR │
//    └─────┴───────┴───────┴───────┼─────────┼─────────┤   ├─────────┼─────────┼─────────┴─────────┴─────────┴──────────┘
//                                  │ TMB_BSP │ TMB_ESC │   │ TMB_ENT │ TMB_SPC │
//                                  └─────────┴─────────┘   └─────────┴─────────┘
[0] = LAYOUT_voyager(
  KC_NO    , KC_NO , KC_NO , KC_NO , KC_NO   , KC_NO   ,     KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,
  KC_GRAVE , KC_Q  , KC_W  , KC_E  , KC_R    , KC_T    ,     KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_EQUAL,
  KC_TAB   , HRM_A , HRM_S , HRM_D , HRM_F   , KC_G    ,     KC_H    , HRM_J   , HRM_K   , HRM_L   , HRM_QUO , KC_MINUS,
  KC_NO    , BRM_Z , BRM_X , BRM_C , BRM_V   , KC_B    ,     KC_N    , BRM_M   , BRM_COM , BRM_DOT , BRM_SLS , BRM_ASTR,
                                     TMB_BSP , TMB_ESC ,     TMB_ENT , TMB_SPC
),

//    ┌──────────┬──────────┬───────────┬──────────┬─────────────┬──────────┐   ┌──────┬──────┬────┬──────┬────┬─────────┐
//    │    no    │    no    │    no     │    no    │     no      │    no    │   │  no  │  no  │ no │  no  │ no │   no    │
//    ├──────────┼──────────┼───────────┼──────────┼─────────────┼──────────┤   ├──────┼──────┼────┼──────┼────┼─────────┤
//    │ SEL_ALL  │ MAC_QUIT │  TAB_CLS  │ TAB_PRV  │   TAB_NXT   │ TAB_OPN  │   │  no  │  (   │ )  │  {   │ }  │   no    │
//    ├──────────┼──────────┼───────────┼──────────┼─────────────┼──────────┤   ├──────┼──────┼────┼──────┼────┼─────────┤
//    │ CYCLOTAB │ left_GUI │ left_CTRL │ left_ALT │ left_SHIFT  │ CW_TOGG  │   │ left │ down │ up │ rght │ :  │ MCR_ARR │
//    ├──────────┼──────────┼───────────┼──────────┼─────────────┼──────────┤   ├──────┼──────┼────┼──────┼────┼─────────┤
//    │ MAC_DEL  │ mAC_UNDO │  mAC_CUT  │ mAC_COPY │  mAC_PASTE  │ MAC_FIND │   │  no  │  [   │ ]  │  <   │ >  │   no    │
//    └──────────┴──────────┴───────────┴──────────┼─────────────┼──────────┤   ├──────┼──────┼────┴──────┴────┴─────────┘
//                                                 │ tRANSPARENT │    no    │   │ ent  │ spc  │
//                                                 └─────────────┴──────────┘   └──────┴──────┘
[1] = LAYOUT_voyager(
  KC_NO    , KC_NO       , KC_NO        , KC_NO       , KC_NO          , KC_NO    ,     KC_NO    , KC_NO    , KC_NO   , KC_NO    , KC_NO   , KC_NO  ,
  SEL_ALL  , MAC_QUIT    , TAB_CLS      , TAB_PRV     , TAB_NXT        , TAB_OPN  ,     KC_NO    , KC_LPRN  , KC_RPRN , KC_LCBR  , KC_RCBR , KC_NO  ,
  CYCLOTAB , KC_LEFT_GUI , KC_LEFT_CTRL , KC_LEFT_ALT , KC_LEFT_SHIFT  , CW_TOGG  ,     KC_LEFT  , KC_DOWN  , KC_UP   , KC_RIGHT , KC_COLN , MCR_ARR,
  MAC_DEL  , KC_MAC_UNDO , KC_MAC_CUT   , KC_MAC_COPY , KC_MAC_PASTE   , MAC_FIND ,     KC_NO    , KC_LBRC  , KC_RBRC , KC_LABK  , KC_RABK , KC_NO  ,
                                                        KC_TRANSPARENT , KC_NO    ,     KC_ENTER , KC_SPACE
),

//    ┌────┬──────────┬───────────┬──────────┬────────────┬─────────────┐   ┌────┬──────┬──────┬──────┬─────────┬────┐
//    │ no │    no    │    no     │    no    │     no     │     no      │   │ no │  no  │  no  │  no  │   no    │ no │
//    ├────┼──────────┼───────────┼──────────┼────────────┼─────────────┤   ├────┼──────┼──────┼──────┼─────────┼────┤
//    │ no │    no    │     +     │    -     │     =      │     no      │   │ no │ DF_7 │ DF_8 │ DF_9 │ DF_ASTR │ no │
//    ├────┼──────────┼───────────┼──────────┼────────────┼─────────────┤   ├────┼──────┼──────┼──────┼─────────┼────┤
//    │ no │ left_GUI │ left_CTRL │ left_ALT │ left_SHIFT │     no      │   │ 0  │ DF_1 │ DF_2 │ DF_3 │  DF_0   │ no │
//    ├────┼──────────┼───────────┼──────────┼────────────┼─────────────┤   ├────┼──────┼──────┼──────┼─────────┼────┤
//    │ no │    no    │     ,     │    .     │     :      │     no      │   │ no │ DF_4 │ DF_5 │ DF_6 │ DF_SLS  │ no │
//    └────┴──────────┴───────────┴──────────┼────────────┼─────────────┤   ├────┼──────┼──────┴──────┴─────────┴────┘
//                                           │     no     │ tRANSPARENT │   │ 0  │ spc  │
//                                           └────────────┴─────────────┘   └────┴──────┘
[2] = LAYOUT_voyager(
  KC_NO , KC_NO       , KC_NO        , KC_NO       , KC_NO         , KC_NO          ,     KC_NO , KC_NO    , KC_NO , KC_NO , KC_NO   , KC_NO,
  KC_NO , KC_NO       , KC_PLUS      , KC_MINUS    , KC_EQUAL      , KC_NO          ,     KC_NO , DF_7     , DF_8  , DF_9  , DF_ASTR , KC_NO,
  KC_NO , KC_LEFT_GUI , KC_LEFT_CTRL , KC_LEFT_ALT , KC_LEFT_SHIFT , KC_NO          ,     KC_0  , DF_1     , DF_2  , DF_3  , DF_0    , KC_NO,
  KC_NO , KC_NO       , KC_COMMA     , KC_DOT      , KC_COLN       , KC_NO          ,     KC_NO , DF_4     , DF_5  , DF_6  , DF_SLS  , KC_NO,
                                                     KC_NO         , KC_TRANSPARENT ,     KC_0  , KC_SPACE
),

//    ┌────┬────┬────┬────┬─────┬─────────────┐   ┌─────┬─────┬────┬──────┬────┬────┐
//    │ no │ no │ no │ no │ no  │     no      │   │ no  │ no  │ no │  no  │ no │ no │
//    ├────┼────┼────┼────┼─────┼─────────────┤   ├─────┼─────┼────┼──────┼────┼────┤
//    │ no │ ~  │ <  │ >  │  %  │   MCR_ARR   │   │ no  │  {  │ }  │  =   │ +  │ no │
//    ├────┼────┼────┼────┼─────┼─────────────┤   ├─────┼─────┼────┼──────┼────┼────┤
//    │ no │ ^  │ @  │ #  │  $  │ MCR_DLR_BRC │   │ no  │  (  │ )  │ kp_- │ `  │ no │
//    ├────┼────┼────┼────┼─────┼─────────────┤   ├─────┼─────┼────┼──────┼────┼────┤
//    │ no │ \  │ |  │ &  │  *  │     no      │   │ no  │  [  │ ]  │  _   │ !  │ no │
//    └────┴────┴────┴────┼─────┼─────────────┤   ├─────┼─────┼────┴──────┴────┴────┘
//                        │ del │     tab     │   │ ent │ spc │
//                        └─────┴─────────────┘   └─────┴─────┘
[3] = LAYOUT_voyager(
  KC_NO , KC_NO   , KC_NO   , KC_NO   , KC_NO     , KC_NO       ,     KC_NO    , KC_NO    , KC_NO   , KC_NO       , KC_NO    , KC_NO,
  KC_NO , KC_TILD , KC_LABK , KC_RABK , KC_PERC   , MCR_ARR     ,     KC_NO    , KC_LCBR  , KC_RCBR , KC_EQUAL    , KC_PLUS  , KC_NO,
  KC_NO , KC_CIRC , KC_AT   , KC_HASH , KC_DLR    , MCR_DLR_BRC ,     KC_NO    , KC_LPRN  , KC_RPRN , KC_KP_MINUS , KC_GRAVE , KC_NO,
  KC_NO , KC_BSLS , KC_PIPE , KC_AMPR , KC_ASTR   , KC_NO       ,     KC_NO    , KC_LBRC  , KC_RBRC , KC_UNDS     , KC_EXLM  , KC_NO,
                                        KC_DELETE , KC_TAB      ,     KC_ENTER , KC_SPACE
),

//    ┌────┬────┬───────────┬───────────┬───────────┬────┐   ┌────┬─────────────┬──────┬──────┬──────────┬────┐
//    │ no │ no │    no     │    no     │    no     │ no │   │ no │     no      │  no  │  no  │    no    │ no │
//    ├────┼────┼───────────┼───────────┼───────────┼────┤   ├────┼─────────────┼──────┼──────┼──────────┼────┤
//    │ no │ no │    no     │   ms_u    │    no     │ no │   │ no │    btn4     │ wh_u │ btn5 │    no    │ no │
//    ├────┼────┼───────────┼───────────┼───────────┼────┤   ├────┼─────────────┼──────┼──────┼──────────┼────┤
//    │ no │ no │   ms_l    │   ms_d    │   ms_r    │ no │   │ no │    btn1     │ btn3 │ btn2 │ rght_GUI │ no │
//    ├────┼────┼───────────┼───────────┼───────────┼────┤   ├────┼─────────────┼──────┼──────┼──────────┼────┤
//    │ no │ no │ mS_ACCEL0 │ mS_ACCEL1 │ mS_ACCEL2 │ no │   │ no │    wh_l     │ wh_d │ wh_r │    no    │ no │
//    └────┴────┴───────────┴───────────┼───────────┼────┤   ├────┼─────────────┼──────┴──────┴──────────┴────┘
//                                      │    no     │ no │   │ no │ tRANSPARENT │
//                                      └───────────┴────┘   └────┴─────────────┘
[4] = LAYOUT_voyager(
  KC_NO , KC_NO , KC_NO        , KC_NO        , KC_NO        , KC_NO ,     KC_NO , KC_NO          , KC_NO         , KC_NO          , KC_NO        , KC_NO,
  KC_NO , KC_NO , KC_NO        , KC_MS_UP     , KC_NO        , KC_NO ,     KC_NO , KC_MS_BTN4     , KC_MS_WH_UP   , KC_MS_BTN5     , KC_NO        , KC_NO,
  KC_NO , KC_NO , KC_MS_LEFT   , KC_MS_DOWN   , KC_MS_RIGHT  , KC_NO ,     KC_NO , KC_MS_BTN1     , KC_MS_BTN3    , KC_MS_BTN2     , KC_RIGHT_GUI , KC_NO,
  KC_NO , KC_NO , KC_MS_ACCEL0 , KC_MS_ACCEL1 , KC_MS_ACCEL2 , KC_NO ,     KC_NO , KC_MS_WH_LEFT  , KC_MS_WH_DOWN , KC_MS_WH_RIGHT , KC_NO        , KC_NO,
                                                KC_NO        , KC_NO ,     KC_NO , KC_TRANSPARENT
),

//    ┌──────────────────┬─────────┬─────────┬─────────┬─────────┬─────────────────┐   ┌────┬────┬──────────┬─────────┬───────────────────┬─────────────┐
//    │        no        │   no    │   no    │   no    │   no    │       no        │   │ no │ no │    no    │   no    │        no         │     no      │
//    ├──────────────────┼─────────┼─────────┼─────────┼─────────┼─────────────────┤   ├────┼────┼──────────┼─────────┼───────────────────┼─────────────┤
//    │ RGB_MODE_FORWARD │ RGB_SPD │ RGB_SPI │ RGB_VAD │ RGB_VAI │  bRIGHTNESS_UP  │   │ no │ no │    no    │   no    │        no         │   QK_BOOT   │
//    ├──────────────────┼─────────┼─────────┼─────────┼─────────┼─────────────────┤   ├────┼────┼──────────┼─────────┼───────────────────┼─────────────┤
//    │     RGB_SLD      │  mprv   │  mnxt   │  vold   │  volu   │ bRIGHTNESS_DOWN │   │ no │ no │    no    │   no    │        no         │     no      │
//    ├──────────────────┼─────────┼─────────┼─────────┼─────────┼─────────────────┤   ├────┼────┼──────────┼─────────┼───────────────────┼─────────────┤
//    │     RGB_TOG      │ RGB_SAD │ RGB_SAI │ RGB_HUD │ RGB_HUI │       no        │   │ no │ no │ MAC_LOCK │ MAC_DND │ mS_JIGGLER_TOGGLE │ tRANSPARENT │
//    └──────────────────┴─────────┴─────────┴─────────┼─────────┼─────────────────┤   ├────┼────┼──────────┴─────────┴───────────────────┴─────────────┘
//                                                     │  mply   │      mute       │   │ no │ no │
//                                                     └─────────┴─────────────────┘   └────┴────┘
[5] = LAYOUT_voyager(
  KC_NO            , KC_NO               , KC_NO               , KC_NO             , KC_NO               , KC_NO              ,     KC_NO , KC_NO , KC_NO    , KC_NO   , KC_NO                , KC_NO         ,
  RGB_MODE_FORWARD , RGB_SPD             , RGB_SPI             , RGB_VAD           , RGB_VAI             , KC_BRIGHTNESS_UP   ,     KC_NO , KC_NO , KC_NO    , KC_NO   , KC_NO                , QK_BOOT       ,
  RGB_SLD          , KC_MEDIA_PREV_TRACK , KC_MEDIA_NEXT_TRACK , KC_AUDIO_VOL_DOWN , KC_AUDIO_VOL_UP     , KC_BRIGHTNESS_DOWN ,     KC_NO , KC_NO , KC_NO    , KC_NO   , KC_NO                , KC_NO         ,
  RGB_TOG          , RGB_SAD             , RGB_SAI             , RGB_HUD           , RGB_HUI             , KC_NO              ,     KC_NO , KC_NO , MAC_LOCK , MAC_DND , KC_MS_JIGGLER_TOGGLE , KC_TRANSPARENT,
                                                                                     KC_MEDIA_PLAY_PAUSE , KC_AUDIO_MUTE      ,     KC_NO , KC_NO
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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HRM_A:
            return TAPPING_TERM + 60;
        case HRM_S:
            return TAPPING_TERM + 20;
        case HRM_D:
            return TAPPING_TERM -10;
        case HRM_F:
            return TAPPING_TERM -20;
        case BRM_Z:
            return TAPPING_TERM + 60;
        case BRM_X:
            return TAPPING_TERM + 20;
        case HRM_J:
            return TAPPING_TERM -20;
        case HRM_K:
            return TAPPING_TERM -10;
        case HRM_L:
            return TAPPING_TERM + 20;
        case BRM_DOT:
            return TAPPING_TERM + 20;
        case BRM_SLS:
            return TAPPING_TERM + 60;
        case BRM_ASTR:
            return TAPPING_TERM + 80;
        default:
            return TAPPING_TERM;
    }
}

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
    break;
    case MCR_DLR_BRC:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_4))SS_DELAY(1)  SS_LSFT(SS_TAP(X_LBRC))SS_DELAY(1)  SS_LSFT(SS_TAP(X_RBRC))SS_DELAY(1)  SS_TAP(X_LEFT));
    }
    break;
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
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}
