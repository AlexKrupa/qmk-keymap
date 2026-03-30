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

// Num/fun keys: number tap, function hold
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

// Home row mods
#define HRM_L4 MT(MOD_LGUI, KC_A)
#define HRM_L3 MT(MOD_LCTL, KC_S)
#define HRM_L2 MT(MOD_LALT, KC_D)
#define HRM_L1 MT(MOD_LSFT, KC_F)

#define HRM_R1 MT(MOD_RSFT, KC_J)
#define HRM_R2 MT(MOD_LALT, KC_K)
#define HRM_R3 MT(MOD_RCTL, KC_L)
#define HRM_R4 MT(MOD_RGUI, KC_QUOTE)

// Bottom row mods
#define BRM_L4 ALL_T(KC_Z)
#define BRM_L3 MEH_T(KC_X)
#define BRM_L2 MT(MOD_RALT, KC_C)
#define BRM_L1 LT(3, KC_V)

#define BRM_R1 LT(3, KC_M)
#define BRM_R2 MT(MOD_RALT, KC_COMMA)
#define BRM_R3 MEH_T(KC_DOT)
#define BRM_R4 ALL_T(KC_SLASH)

// Thumbs
#define TMB_L1 LT(1, KC_BSPC)
#define TMB_L2 LT(2, KC_ESCAPE)

#define TMB_R2 LT(3, KC_ENTER)
#define TMB_R1 LT(4, KC_SPACE)

// Shortcuts
#define KC_MAC_DELETE LGUI(KC_BSPC)
#define KC_SELECT_ALL LGUI(KC_A)
#define KC_QUIT       LGUI(KC_Q)
#define KC_TAB_CLOSE  LGUI(KC_W)
#define KC_TAB_PREV   LCTL(LSFT(KC_TAB))
#define KC_TAB_NEXT   LCTL(KC_TAB)
#define KC_TAB_OPEN   LGUI(KC_T)
#define KC_FIND       LGUI(KC_F)
#define KC_CYCLOTAB   LGUI(KC_TAB)



// Custom shift keys: add entries to remap Shift+key behavior.
// Each entry is {key, shifted_key}. Examples:
//   {KC_DOT,  KC_QUES},  // Shift + . = ?
const custom_shift_key_t custom_shift_keys[] = {
  {BRM_R2, KC_SCLN},  // ,;
  {BRM_R3, KC_COLN},   // .:
  {KC_ASTR, KC_EXLM}   // *!
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌────────────┬────────┬────────┬────────┬────────┬────────┐   ┌────────┬────────┬────────┬────────┬────────┬───────────┐
//    │     no     │   no   │   no   │   no   │   no   │   no   │   │   no   │   no   │   no   │   no   │   no   │ LT(5, no) │
//    ├────────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼───────────┤
//    │     `      │   q    │   w    │   e    │   r    │   t    │   │   y    │   u    │   i    │   o    │   p    │     =     │
//    ├────────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼───────────┤
//    │    tab     │ HRM_L4 │ HRM_L3 │ HRM_L2 │ HRM_L1 │   g    │   │   h    │ HRM_R1 │ HRM_R2 │ HRM_R3 │ HRM_R4 │     -     │
//    ├────────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼───────────┤
//    │ left_SHIFT │ BRM_L4 │ BRM_L3 │ BRM_L2 │ BRM_L1 │   b    │   │   n    │ BRM_R1 │ BRM_R2 │ BRM_R3 │ BRM_R4 │     *     │
//    └────────────┴────────┴────────┴────────┼────────┼────────┤   ├────────┼────────┼────────┴────────┴────────┴───────────┘
//                                            │ TMB_L1 │ TMB_L2 │   │ TMB_R2 │ TMB_R1 │
//                                            └────────┴────────┘   └────────┴────────┘
[0] = LAYOUT_voyager(
  KC_NO         , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,     KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , LT(5, KC_NO),
  KC_GRAVE      , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQUAL    ,
  KC_TAB        , HRM_L4 , HRM_L3 , HRM_L2 , HRM_L1 , KC_G   ,     KC_H   , HRM_R1 , HRM_R2 , HRM_R3 , HRM_R4 , KC_MINUS    ,
  KC_LEFT_SHIFT , BRM_L4 , BRM_L3 , BRM_L2 , BRM_L1 , KC_B   ,     KC_N   , BRM_R1 , BRM_R2 , BRM_R3 , BRM_R4 , KC_ASTR     ,
                                             TMB_L1 , TMB_L2 ,     TMB_R2 , TMB_R1
),

//    ┌────────────┬──────────┬───────────┬──────────┬─────────────┬──────────┐   ┌──────┬──────┬────┬──────┬────┬────────────┐
//    │     no     │    no    │    no     │    no    │     no      │    no    │   │  no  │  no  │ no │  no  │ no │     no     │
//    ├────────────┼──────────┼───────────┼──────────┼─────────────┼──────────┤   ├──────┼──────┼────┼──────┼────┼────────────┤
//    │ select_ALL │   qUIT   │ tab_CLOSE │ tab_PREV │  tab_NEXT   │ tab_OPEN │   │  no  │  (   │ )  │  {   │ }  │     no     │
//    ├────────────┼──────────┼───────────┼──────────┼─────────────┼──────────┤   ├──────┼──────┼────┼──────┼────┼────────────┤
//    │  cYCLOTAB  │ left_GUI │ left_CTRL │ left_ALT │ left_SHIFT  │ CW_TOGG  │   │ left │ down │ up │ rght │ :  │ ST_MACRO_0 │
//    ├────────────┼──────────┼───────────┼──────────┼─────────────┼──────────┤   ├──────┼──────┼────┼──────┼────┼────────────┤
//    │ mAC_DELETE │ mAC_UNDO │  mAC_CUT  │ mAC_COPY │  mAC_PASTE  │   find   │   │  no  │  [   │ ]  │  <   │ >  │     no     │
//    └────────────┴──────────┴───────────┴──────────┼─────────────┼──────────┤   ├──────┼──────┼────┴──────┴────┴────────────┘
//                                                   │ tRANSPARENT │    no    │   │ ent  │ spc  │
//                                                   └─────────────┴──────────┘   └──────┴──────┘
[1] = LAYOUT_voyager(
  KC_NO         , KC_NO       , KC_NO        , KC_NO       , KC_NO          , KC_NO       ,     KC_NO    , KC_NO    , KC_NO   , KC_NO    , KC_NO   , KC_NO     ,
  KC_SELECT_ALL , KC_QUIT     , KC_TAB_CLOSE , KC_TAB_PREV , KC_TAB_NEXT    , KC_TAB_OPEN ,     KC_NO    , KC_LPRN  , KC_RPRN , KC_LCBR  , KC_RCBR , KC_NO     ,
  KC_CYCLOTAB   , KC_LEFT_GUI , KC_LEFT_CTRL , KC_LEFT_ALT , KC_LEFT_SHIFT  , CW_TOGG     ,     KC_LEFT  , KC_DOWN  , KC_UP   , KC_RIGHT , KC_COLN , ST_MACRO_0,
  KC_MAC_DELETE , KC_MAC_UNDO , KC_MAC_CUT   , KC_MAC_COPY , KC_MAC_PASTE   , KC_FIND     ,     KC_NO    , KC_LBRC  , KC_RBRC , KC_LABK  , KC_RABK , KC_NO     ,
                                                             KC_TRANSPARENT , KC_NO       ,     KC_ENTER , KC_SPACE
),

//    ┌────┬──────────┬───────────┬──────────┬────────────┬─────────────┐   ┌────┬─────────────┬─────────────┬──────────────┬──────────────┬────┐
//    │ no │    no    │    no     │    no    │     no     │     no      │   │ no │     no      │     no      │      no      │      no      │ no │
//    ├────┼──────────┼───────────┼──────────┼────────────┼─────────────┤   ├────┼─────────────┼─────────────┼──────────────┼──────────────┼────┤
//    │ no │    no    │     +     │    -     │     =      │     no      │   │ no │ DUAL_FUNC_0 │ DUAL_FUNC_1 │ DUAL_FUNC_2  │ DUAL_FUNC_3  │ no │
//    ├────┼──────────┼───────────┼──────────┼────────────┼─────────────┤   ├────┼─────────────┼─────────────┼──────────────┼──────────────┼────┤
//    │ no │ left_GUI │ left_CTRL │ left_ALT │ left_SHIFT │     no      │   │ 0  │ DUAL_FUNC_4 │ DUAL_FUNC_5 │ DUAL_FUNC_6  │ DUAL_FUNC_7  │ no │
//    ├────┼──────────┼───────────┼──────────┼────────────┼─────────────┤   ├────┼─────────────┼─────────────┼──────────────┼──────────────┼────┤
//    │ no │    no    │     ,     │    .     │     :      │     no      │   │ no │ DUAL_FUNC_8 │ DUAL_FUNC_9 │ DUAL_FUNC_10 │ DUAL_FUNC_11 │ no │
//    └────┴──────────┴───────────┴──────────┼────────────┼─────────────┤   ├────┼─────────────┼─────────────┴──────────────┴──────────────┴────┘
//                                           │     no     │ tRANSPARENT │   │ 0  │     spc     │
//                                           └────────────┴─────────────┘   └────┴─────────────┘
[2] = LAYOUT_voyager(
  KC_NO , KC_NO       , KC_NO        , KC_NO       , KC_NO         , KC_NO          ,     KC_NO , KC_NO       , KC_NO       , KC_NO        , KC_NO        , KC_NO,
  KC_NO , KC_NO       , KC_PLUS      , KC_MINUS    , KC_EQUAL      , KC_NO          ,     KC_NO , DUAL_FUNC_0 , DUAL_FUNC_1 , DUAL_FUNC_2  , DUAL_FUNC_3  , KC_NO,
  KC_NO , KC_LEFT_GUI , KC_LEFT_CTRL , KC_LEFT_ALT , KC_LEFT_SHIFT , KC_NO          ,     KC_0  , DUAL_FUNC_4 , DUAL_FUNC_5 , DUAL_FUNC_6  , DUAL_FUNC_7  , KC_NO,
  KC_NO , KC_NO       , KC_COMMA     , KC_DOT      , KC_COLN       , KC_NO          ,     KC_NO , DUAL_FUNC_8 , DUAL_FUNC_9 , DUAL_FUNC_10 , DUAL_FUNC_11 , KC_NO,
                                                     KC_NO         , KC_TRANSPARENT ,     KC_0  , KC_SPACE
),

//    ┌────┬────┬────┬────┬─────┬────────────┐   ┌─────┬─────┬────┬──────┬────┬────┐
//    │ no │ no │ no │ no │ no  │     no     │   │ no  │ no  │ no │  no  │ no │ no │
//    ├────┼────┼────┼────┼─────┼────────────┤   ├─────┼─────┼────┼──────┼────┼────┤
//    │ no │ ~  │ <  │ >  │  %  │ ST_MACRO_1 │   │ no  │  {  │ }  │  =   │ +  │ no │
//    ├────┼────┼────┼────┼─────┼────────────┤   ├─────┼─────┼────┼──────┼────┼────┤
//    │ no │ ^  │ @  │ #  │  $  │ ST_MACRO_2 │   │ no  │  (  │ )  │ kp_- │ `  │ no │
//    ├────┼────┼────┼────┼─────┼────────────┤   ├─────┼─────┼────┼──────┼────┼────┤
//    │ no │ \  │ |  │ &  │  *  │     no     │   │ no  │  [  │ ]  │  _   │ !  │ no │
//    └────┴────┴────┴────┼─────┼────────────┤   ├─────┼─────┼────┴──────┴────┴────┘
//                        │ del │    tab     │   │ ent │ spc │
//                        └─────┴────────────┘   └─────┴─────┘
[3] = LAYOUT_voyager(
  KC_NO , KC_NO   , KC_NO   , KC_NO   , KC_NO     , KC_NO      ,     KC_NO    , KC_NO    , KC_NO   , KC_NO       , KC_NO    , KC_NO,
  KC_NO , KC_TILD , KC_LABK , KC_RABK , KC_PERC   , ST_MACRO_1 ,     KC_NO    , KC_LCBR  , KC_RCBR , KC_EQUAL    , KC_PLUS  , KC_NO,
  KC_NO , KC_CIRC , KC_AT   , KC_HASH , KC_DLR    , ST_MACRO_2 ,     KC_NO    , KC_LPRN  , KC_RPRN , KC_KP_MINUS , KC_GRAVE , KC_NO,
  KC_NO , KC_BSLS , KC_PIPE , KC_AMPR , KC_ASTR   , KC_NO      ,     KC_NO    , KC_LBRC  , KC_RBRC , KC_UNDS     , KC_EXLM  , KC_NO,
                                        KC_DELETE , KC_TAB     ,     KC_ENTER , KC_SPACE
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
