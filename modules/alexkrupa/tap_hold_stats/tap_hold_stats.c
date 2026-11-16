#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keycode_string.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

#define SLOT_COUNT 24
#define UNDER_MS 100
#define BUCKET_MS 10
#define OVER_MS 350
// `under`, one bucket per BUCKET_MS from UNDER_MS to OVER_MS, `over`.
#define BUCKET_COUNT (1 + (OVER_MS - UNDER_MS) / BUCKET_MS + 1)

enum context { CONTEXT_ALONE, CONTEXT_OVERLAP, CONTEXT_COUNT };
enum decision { DECISION_TAP, DECISION_HOLD, DECISION_COUNT };

static const char *const context_names[CONTEXT_COUNT] = {"alone", "overlap"};
static const char *const decision_names[DECISION_COUNT] = {"tap", "hold"};

// Holds only: a hold shorter than the term is a probable false hold.
enum hold_length { HOLD_SHORT, HOLD_LONG, HOLD_LENGTH_COUNT };
enum previous_key { PREVIOUS_LETTER, PREVIOUS_SPACE, PREVIOUS_OTHER, PREVIOUS_COUNT };

static const char *const hold_length_names[HOLD_LENGTH_COUNT] = {"short", "long"};
static const char *const previous_key_names[PREVIOUS_COUNT] = {"letter", "space", "other"};

// Lower bounds in ms of the time from the previous key event to the press.
static const uint16_t idle_bucket_starts_ms[] = {0, 50, 100, 150, 200, 500};
#define IDLE_BUCKET_COUNT (sizeof(idle_bucket_starts_ms) / sizeof(idle_bucket_starts_ms[0]))

enum phase { PHASE_IDLE, PHASE_DOWN, PHASE_RELEASED };
enum pending { PENDING_NONE, PENDING_TAP, PENDING_HOLD, PENDING_SKIP };

typedef struct {
  uint16_t press_time;
  uint16_t release_time;
  uint8_t phase : 2;
  // Set by the resolved press, because the release tap.count is not reliable.
  uint8_t pending : 2;
  uint8_t overlap : 1;
  uint8_t previous_key : 2;
  uint8_t idle_bucket : 3;
} raw_state_t;

typedef struct {
  uint16_t keycode;
  keypos_t key;
  uint16_t term;
  uint16_t counts[CONTEXT_COUNT][DECISION_COUNT][BUCKET_COUNT];
  uint16_t idle_counts[HOLD_LENGTH_COUNT][PREVIOUS_COUNT][IDLE_BUCKET_COUNT];
} slot_t;

static raw_state_t raw_states[MATRIX_ROWS][MATRIX_COLS];
static slot_t slots[SLOT_COUNT];
static uint32_t press_count = 0;
// 32-bit, because a 16-bit difference wraps after a pause of 65 s.
static uint32_t last_event_ms = 0;
static uint8_t last_event_previous_key = PREVIOUS_OTHER;
static bool has_last_event = false;

static uint8_t bucket_index(uint16_t duration_ms) {
  if (duration_ms < UNDER_MS) return 0;
  if (duration_ms >= OVER_MS) return BUCKET_COUNT - 1;
  return 1 + (duration_ms - UNDER_MS) / BUCKET_MS;
}

static uint8_t idle_bucket_index(uint32_t idle_ms) {
  uint8_t index = IDLE_BUCKET_COUNT - 1;
  while (idle_ms < idle_bucket_starts_ms[index]) index--;
  return index;
}

static uint8_t previous_key_index(uint16_t keycode) {
  uint16_t tap_keycode = get_tap_keycode(keycode);
  if (KC_A <= tap_keycode && tap_keycode <= KC_Z) return PREVIOUS_LETTER;
  if (tap_keycode == KC_SPC) return PREVIOUS_SPACE;
  return PREVIOUS_OTHER;
}

static slot_t *find_slot(keypos_t key, uint16_t keycode) {
  for (uint8_t i = 0; i < SLOT_COUNT; i++) {
    slot_t *slot = &slots[i];
    if (slot->keycode == 0) {
      slot->keycode = keycode;
      slot->key = key;
      return slot;
    }
    if (slot->key.row == key.row && slot->key.col == key.col) return slot;
  }
  return NULL;
}

// Needs the resolved keycode: at raw press time, a pending LT() has not changed the layer yet.
static bool is_tracked(uint16_t keycode, keyrecord_t *record) {
  return (IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode)) &&
         keycode == keymap_key_to_keycode(0, record->event.key);
}

static void add_press(raw_state_t *raw, uint16_t keycode, keyrecord_t *record) {
  slot_t *slot = find_slot(record->event.key, keycode);
  if (slot == NULL) return;

  uint8_t context      = raw->overlap ? CONTEXT_OVERLAP : CONTEXT_ALONE;
  uint8_t decision     = raw->pending == PENDING_TAP ? DECISION_TAP : DECISION_HOLD;
  uint16_t duration_ms = TIMER_DIFF_16(raw->release_time, raw->press_time);
  uint16_t *count      = &slot->counts[context][decision][bucket_index(duration_ms)];
  if (*count < UINT16_MAX) (*count)++;
  slot->term = get_tapping_term(keycode, record);

  if (decision == DECISION_HOLD) {
    uint8_t length       = duration_ms < slot->term ? HOLD_SHORT : HOLD_LONG;
    uint16_t *idle_count = &slot->idle_counts[length][raw->previous_key][raw->idle_bucket];
    if (*idle_count < UINT16_MAX) (*idle_count)++;
  }
}

// No TAP_CODE_DELAY: with it, a dump of a day of data takes minutes.
static void send_text(const char *text) {
  send_string_with_delay(text, 0);
}

static void send_newline(void) {
  // Shift+Enter, so a dump into a chat input does not submit it.
  SEND_STRING_DELAY(SS_LSFT(SS_TAP(X_ENTER)), 0);
}

static void send_bucket(uint8_t index, uint16_t count) {
  char text[16];
  if (index == 0) {
    snprintf(text, sizeof(text), " under=%u", (unsigned)count);
  } else if (index == BUCKET_COUNT - 1) {
    snprintf(text, sizeof(text), " over=%u", (unsigned)count);
  } else {
    snprintf(text, sizeof(text), " %u=%u", (unsigned)(UNDER_MS / BUCKET_MS + index - 1), (unsigned)count);
  }
  send_text(text);
}

static void send_histogram(const slot_t *slot, uint8_t context, uint8_t decision) {
  const uint16_t *counts = slot->counts[context][decision];
  uint32_t total = 0;
  for (uint8_t i = 0; i < BUCKET_COUNT; i++) total += counts[i];
  if (total == 0) return;

  char text[32];
  snprintf(text, sizeof(text), "  %s %s n=%lu", context_names[context], decision_names[decision],
           (unsigned long)total);
  send_text(text);
  for (uint8_t i = 0; i < BUCKET_COUNT; i++) {
    if (counts[i] > 0) send_bucket(i, counts[i]);
  }
  send_newline();
}

static void send_idle_histogram(const slot_t *slot, uint8_t length, uint8_t previous_key) {
  const uint16_t *counts = slot->idle_counts[length][previous_key];
  uint32_t total = 0;
  for (uint8_t i = 0; i < IDLE_BUCKET_COUNT; i++) total += counts[i];
  if (total == 0) return;

  char text[48];
  snprintf(text, sizeof(text), "  %s hold after=%s n=%lu", hold_length_names[length],
           previous_key_names[previous_key], (unsigned long)total);
  send_text(text);
  for (uint8_t i = 0; i < IDLE_BUCKET_COUNT; i++) {
    if (counts[i] > 0) {
      snprintf(text, sizeof(text), " %u=%u", (unsigned)idle_bucket_starts_ms[i], (unsigned)counts[i]);
      send_text(text);
    }
  }
  send_newline();
}

static void dump(void) {
  char text[96];
  snprintf(text, sizeof(text), "tap_hold_stats uptime=%lu presses=%lu bucket=%ums under=0-%ums over=%ums",
           (unsigned long)(timer_read32() / 1000), (unsigned long)press_count, (unsigned)BUCKET_MS,
           (unsigned)(UNDER_MS - 1), (unsigned)OVER_MS);
  send_text(text);
  send_newline();

  for (uint8_t i = 0; i < SLOT_COUNT && slots[i].keycode != 0; i++) {
    const slot_t *slot = &slots[i];
    // get_keycode_string() returns a static buffer, so send it before the next call.
    send_text(get_keycode_string(slot->keycode));
    snprintf(text, sizeof(text), " term=%u", (unsigned)slot->term);
    send_text(text);
    send_newline();
    for (uint8_t context = 0; context < CONTEXT_COUNT; context++) {
      for (uint8_t decision = 0; decision < DECISION_COUNT; decision++) {
        send_histogram(slot, context, decision);
      }
    }
    for (uint8_t length = 0; length < HOLD_LENGTH_COUNT; length++) {
      for (uint8_t previous_key = 0; previous_key < PREVIOUS_COUNT; previous_key++) {
        send_idle_histogram(slot, length, previous_key);
      }
    }
  }
  send_text("time=");
}

bool pre_process_record_tap_hold_stats(uint16_t keycode, keyrecord_t *record) {
  if (!IS_KEYEVENT(record->event)) return true;

  raw_state_t *raw = &raw_states[record->event.key.row][record->event.key.col];
  uint32_t now_ms  = timer_read32();
  if (record->event.pressed) {
    press_count++;
    raw->previous_key = last_event_previous_key;
    raw->idle_bucket  = has_last_event ? idle_bucket_index(now_ms - last_event_ms) : IDLE_BUCKET_COUNT - 1;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        if (raw_states[row][col].phase == PHASE_DOWN) raw_states[row][col].overlap = true;
      }
    }
    raw->press_time = record->event.time;
    raw->overlap    = false;
    raw->phase      = PHASE_DOWN;
    raw->pending    = PENDING_NONE;
  } else if (raw->phase == PHASE_DOWN) {
    raw->release_time = record->event.time;
    raw->phase        = PHASE_RELEASED;
  }
  last_event_ms           = now_ms;
  last_event_previous_key = previous_key_index(keycode);
  has_last_event          = true;
  return true;
}

bool process_record_tap_hold_stats(uint16_t keycode, keyrecord_t *record) {
  if (keycode == TAP_HOLD_STATS_DUMP) {
    if (record->event.pressed) {
      dump();
    }
    return false;
  }
  if (!IS_KEYEVENT(record->event) || !is_tracked(keycode, record)) return true;

  raw_state_t *raw = &raw_states[record->event.key.row][record->event.key.col];
  if (record->event.pressed) {
    // tap.count > 1 is a quick-tap repeat, for example a double letter.
    switch (record->tap.count) {
      case 0:  raw->pending = PENDING_HOLD; break;
      case 1:  raw->pending = PENDING_TAP;  break;
      default: raw->pending = PENDING_SKIP; break;
    }
    return true;
  }
  // A synthetic release can come before the raw release. The phase check drops it.
  if (raw->phase == PHASE_RELEASED && (raw->pending == PENDING_TAP || raw->pending == PENDING_HOLD)) {
    add_press(raw, keycode, record);
  }
  raw->pending = PENDING_NONE;
  return true;
}
