#include "ddrcode.h"

enum layerNames {
    QWERTY,
    COLEMAK,
    EMPTY,
    SYMBOLS
};

char wpm_buff[5];

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case CKC_JP:
            SEND_STRING("Qikitarjurak2022\n");
            break;
        case CKC_BL:
            default_layer_set(default_layer_state == 1 ? (1<<2) : 1);
            break;
        case CKC_WPM:
            #ifdef WPM_ENABLE
            itoa(get_current_wpm(), wpm_buff, 10);
            SEND_STRING(wpm_buff);
            #endif
            break;
        }
    }
    return process_record_keymap(keycode, record);
}


#if defined(RGB_MATRIX_ENABLE)
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
    case QWERTY:
        rgb_matrix_set_color_all (0xFF,  0x00, 0x00);
        break;
    case COLEMAK:
        rgb_matrix_set_color_all (0x00,  0x00, 0x99);
        break;
    case EMPTY:
        rgb_matrix_set_color_all (0x22,  0x22, 0x35);
        break;
    case SYMBOLS:
        rgb_matrix_set_color_all (0x00,  0x99, 0x00);
        break;
    default:
        rgb_matrix_set_color_all (0xFF,  0xFF, 0xFF);
        break;
    }
}
#endif
