#include "helpers.h"
#include "ddrcode.h"

bool is_default_layer_colemak(void) {
    return get_highest_layer(default_layer_state) == COLEMAK;
}

bool is_default_layer_qwerty(void) {
    return get_highest_layer(default_layer_state) == QWERTY;
}

bool is_layer_key(uint16_t keycode) {
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