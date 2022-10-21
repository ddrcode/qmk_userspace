#include "ddrcode.h"

#ifdef WPM_ENABLE
char wpm_buff[5];
#endif

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

__attribute__((weak)) bool process_secrets(uint16_t keycode, keyrecord_t *record) {
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
    return process_secrets(keycode, record) && process_record_keymap(keycode, record);
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



