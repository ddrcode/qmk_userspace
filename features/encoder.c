#include "ddrcode.h"

#if defined(ENCODER_ENABLE)

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][1][2] = {
    [QWERTY] =     { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [COLEMAK] =    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [DEFAULT] =    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [SYMBOLS] =    { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [NAVIGATION] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) }
};

#else

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return false;
}

#endif
#endif
