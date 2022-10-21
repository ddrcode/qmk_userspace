#include "ddrcode.h"

enum layerNames { QWERTY, COLEMAK, DEFAULT, SYMBOLS, NAVIGATION };

#ifdef WPM_ENABLE
char wpm_buff[5];
#endif

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case CKC_SEC1:
                SEND_STRING("ls -al\n");
                break;
            case CKC_BL:
                default_layer_set((default_layer_state & QWERTY) ? (1 << COLEMAK) : (1 << QWERTY));
                break;
            case CKC_WPM:
#ifdef WPM_ENABLE
                itoa(get_current_wpm(), wpm_buff, 10);
                SEND_STRING(wpm_buff);
#endif
                break;
            case CKC_LL:
                SEND_STRING("ls -al\n");
                break;
        }
    }
    return process_record_keymap(keycode, record);
}

#if defined(RGB_MATRIX_ENABLE)
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case QWERTY:
            rgb_matrix_set_color_all(0xFF, 0x00, 0x00);
            break;
        case COLEMAK:
            rgb_matrix_set_color_all(0x00, 0x00, 0x99);
            break;
        case DEFAULT:
            rgb_matrix_set_color_all(0x22, 0x22, 0x35);
            break;
        case SYMBOLS:
            rgb_matrix_set_color_all(0x00, 0x99, 0x00);
            break;
        default:
            rgb_matrix_set_color_all(0xFF, 0xFF, 0xFF);
            break;
    }
}
#endif

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


#if defined(KEY_OVERRIDE_ENABLE)
const key_override_t ctrl_s_colemak_override = ko_make_with_layers(MOD_MASK_CTRL, KC_R, C(KC_S), 2);
const key_override_t cmd_s_colemak_override  = ko_make_with_layers(MOD_MASK_GUI, KC_R, G(KC_S), 2);
const key_override_t ctrl_f_colemak_override = ko_make_with_layers(MOD_MASK_CTRL, KC_T, C(KC_F), 2);
const key_override_t cmd_f_colemak_override  = ko_make_with_layers(MOD_MASK_GUI, KC_T, G(KC_F), 2);

const key_override_t **key_overrides = (const key_override_t *[]){
    &ctrl_s_colemak_override, &cmd_s_colemak_override, &ctrl_f_colemak_override, &cmd_f_colemak_override,
    NULL // Null terminate the array of overrides!
};
#endif
