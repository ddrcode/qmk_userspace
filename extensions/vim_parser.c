#include <stdbool.h>
#include <math.h>
#include "vim.h"

#define MAX_SEQ_SIZE 10

static const kc_t MODE_KEYS[] = { KC_D, KC_V, 0 };
static const kc_t NAV_KEYS[] = { KC_0, KC_P0, KC_H, KC_J, KC_K, KC_L, KC_LEFT, KC_RIGHT, KC_UP, KC_DOWN, 
                                 KC_B, KC_E, S(KC_G), S(KC_4), 0 };

static bool has_keycode(kc_t kc, kc_t const * const arr) {
    for (int i=0; arr[i] > 0; ++i) {
        if (arr[i] == kc) return true;
    }
    return false;
}

static inline bool is_nav(kc_t kc) {
    return has_keycode(kc, NAV_KEYS);
}

static inline bool is_mode(kc_t kc) {
    return has_keycode(kc, MODE_KEYS);
}

static uint16_t parse_num(vi_seq_t seq, uint8_t * i) {
    uint16_t num = 0;
    uint8_t s = *i;
    uint8_t len = s;
    while (is_kc_digit(seq[++len])) ++(*i);
    for (int8_t j=--len; j>=s; --j) {
        num += kc2digit(seq[j]) * pow(10, len-j);
    }
    return num;
}

static vi_mode_t kc2mode(kc_t kc) {
    switch(kc) {
        case KC_D: return DELETE;
        case KC_V: return SELECTION;
    }
    return NORMAL;
}

bool parse_vi_seq(vi_seq_t seq, vi_cmd_t * cmd) {
    if (seq[0] == 0) return true;
    bool mod = false;
    bool nav = false;
    kc_t prev = 0;

    for (uint8_t i=0; i<MAX_SEQ_SIZE && seq[i] != 0; ++i) {
        uint16_t keycode = seq[i];
        if (is_nav(keycode) || (is_kc_zero(keycode) && !is_kc_digit(prev))) {
            if (nav && !is_nav(prev)) return false;
            nav = true;
            if (cmd) cmd->cmd = keycode;
        } 
        else if (is_kc_digit(keycode)) {
            if (nav) return false;
            if (cmd) cmd->rep = parse_num(seq, &i);
        }
        else if (is_mode(keycode)) {
            if (mod || nav) return false;
            mod = true;
            if (cmd) cmd->mode = kc2mode(keycode);
        }
        else {
            return false;
        }
        prev = keycode;
    }
    return true; 
}

bool is_complete(vi_cmd_t * const cmd) {
    return cmd->cmd > 0;
}

void clear_seq(vi_seq_t seq) {
    for (uint8_t i=0; i<MAX_SEQ_SIZE; ++i) {
        seq[i] = 0;
    }
}
