#include <stdbool.h>
#include "vim.h"

static const kc_t MODE_KEYS[] = { KC_C, KC_D, KC_G, KC_V, 0 };
static const kc_t NAV_KEYS[] = { KC_0, KC_P0, KC_H, KC_J, KC_K, KC_L, 
                                 KC_LEFT, KC_RIGHT, KC_UP, KC_DOWN, 
                                 KC_B, KC_E, KC_W, S(KC_G), S(KC_4), 
                                 S(KC_6), S(KC_MINUS), 0 };
static const kc_t EDIT_KEYS[] = { KC_I, S(KC_I), KC_A, S(KC_A), KC_O, S(KC_O),
                                  S(KC_J), KC_S, KC_R, KC_DOT,
                                  KC_BACKSPACE, KC_X, S(KC_X), KC_DEL, 
                                  KC_U, C(KC_R), KC_P, 0 };

static bool has_keycode(kc_t kc, kc_t const * const arr) {
    for (int i=0; arr[i] > 0; ++i) {
        if (arr[i] == kc) return true;
    }
    return false;
}

static inline bool is_nav(kc_t kc) {
    return has_keycode(kc, NAV_KEYS);
}

static inline bool is_edit(kc_t kc) {
    return has_keycode(kc, EDIT_KEYS);
}

static inline bool is_mode(kc_t kc) {
    return has_keycode(kc, MODE_KEYS);
}

static inline bool is_cmd(kc_t keycode, vi_mode_t mode) {
    if (is_nav(keycode) || (is_edit(keycode) && mode == VI_NORMAL_MODE)) return true;
    if (is_mode(keycode)) return kc2mode(keycode) == mode;  // case for cc, gg, yy, vv, dd
    switch(keycode) {
        case S(KC_J): return mode == VI_JUMP_MODE;
        case KC_Y: return mode == VI_SELECTION_MODE;
    }
    return false;
}

static uint16_t parse_num(vi_seq_t seq, uint8_t * i) {
    uint16_t num = 0;
    uint8_t s = *i;
    uint8_t len = s;
    while (is_kc_digit(seq[++len])) ++(*i);
    for (int8_t j=--len; j>=s; --j) {
        num += kc2digit(seq[j]) * int_pow10(len-j);
    }
    return num;
}

vi_mode_t kc2mode(kc_t kc) {
    switch(kc) {
        case KC_C: return VI_CHANGE_MODE;
        case KC_D: return VI_DELETE_MODE;
        case KC_G: return VI_JUMP_MODE;
        case KC_I: return VI_INSERT_MODE;
        case KC_Y: return VI_YANK_MODE;
        case KC_V: return VI_SELECTION_MODE;
    }
    return VI_NORMAL_MODE;
}

bool parse_vi_seq(vi_seq_t seq, vi_cmd_t * cmd) {
    if (seq[0] == 0) return true;
    bool mod = false;
    bool nav = false;
    kc_t prev = 0;

    for (uint8_t i=0; i<VI_SEQ_SIZE && seq[i] != 0; ++i) {
        uint16_t keycode = seq[i];
        if (is_cmd(keycode, cmd->mode) || (is_kc_zero(keycode) && !is_kc_digit(prev))) { 
            if (nav && !is_cmd(prev, cmd->mode)) return false;
            nav = true;
            if (cmd) cmd->keycode = keycode;
        } 
        else if (is_kc_digit(keycode)) {
            if (nav) return false;
            if (cmd) cmd->rep = parse_num(seq, &i);
        }
        else if (is_mode(keycode)) {
            if (mod || nav) return false;
            mod = true;
            cmd->mode = kc2mode(keycode);
        }
        else {
            return false;
        }
        prev = keycode;
    }
    return true;
}

bool is_vi_seq_complete(vi_cmd_t * const cmd) {
    return cmd->keycode > 0;
}

