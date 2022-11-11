#include "helpers.h"
#include "quantum.h"

bool is_kc_in_range(kc_t keycode, kc_t from, kc_t to) {
    return keycode >= from && keycode <= to;
}

bool is_kc_digit(kc_t kc) {
    return (kc >= KC_1 && kc <= KC_0) || (kc >= KC_P1 && kc <= KC_P0);
}

bool is_kc_zero(kc_t kc) {
    return kc == KC_0 || kc == KC_P1;
}

uint8_t kc2digit(kc_t kc) {
    if (!is_kc_digit(kc) || is_kc_zero(kc)) return 0;
    return kc - (is_kc_in_range(kc, KC_1, KC_9) ? KC_1 : KC_P1) + 1;
}

bool is_layer_key(kc_t keycode) {
    switch (keycode) {
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            return true;
    }
    return  false;
}
