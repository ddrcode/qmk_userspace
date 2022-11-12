#include "extensions/vim.h"
#include "helpers/helpers.h"

kc_t vi_key_override_qwerty(kc_t keycode) {
    switch(keycode) {
        // navigation
        case KC_I: return KC_K;
        case KC_J: return KC_H;
        case KC_K: return KC_J;

        // edits
        case KC_H: return KC_I;
        case S(KC_H): return S(KC_I);
        case KC_BSLS: return KC_I;
    }
    return keycode;
}

kc_t vi_key_override_colemak(kc_t keycode) {
    switch(keycode) {
        // navigation
        case KC_U: return KC_K;
        case KC_N: return KC_H;
        case KC_E: return KC_J;
        case KC_I: return KC_L;

        // edits
        case KC_H: return KC_I;
        case S(KC_H): return S(KC_I);
        case KC_BSLS: return KC_I;
    }
    return keycode;
}

kc_t vi_key_override(kc_t keycode) {
    return is_default_layer_colemak() 
         ? vi_key_override_colemak(keycode) 
         : vi_key_override_qwerty(keycode);
}
