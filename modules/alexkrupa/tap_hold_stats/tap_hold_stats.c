#include QMK_KEYBOARD_H
#include <stdio.h>

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

static uint32_t press_count = 0;

static void send_newline(void) {
  // Shift+Enter, so a dump into a chat input does not submit it.
  SEND_STRING(SS_LSFT(SS_TAP(X_ENTER)));
}

static void dump(void) {
  char text[96];
  snprintf(text, sizeof(text), "tap_hold_stats uptime=%lu presses=%lu bucket=10ms under=0-99ms over=350ms",
           (unsigned long)(timer_read32() / 1000), (unsigned long)press_count);
  send_string(text);
  send_newline();
  send_string("time=");
}

bool pre_process_record_tap_hold_stats(uint16_t keycode, keyrecord_t *record) {
  if (IS_KEYEVENT(record->event) && record->event.pressed) {
    press_count++;
  }
  return true;
}

bool process_record_tap_hold_stats(uint16_t keycode, keyrecord_t *record) {
  if (keycode == TAP_HOLD_STATS_DUMP) {
    if (record->event.pressed) {
      dump();
    }
    return false;
  }
  return true;
}
