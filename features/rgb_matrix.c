#include "ddrcode.h"

/*
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, __, 13, 14 },
        { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 },
        { 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48 },
        { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 49, 62, 15, 32 },
        { 63, __, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, __, 74, 86, 75 },
        { 76, 77, 78, __, __, __, 79, __, __, __, 80, 81, 82, 83, 84, 85 },
    },
*/

#ifdef RGB_MATRIX_ENABLE
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

    uint8_t mods = get_mods() | get_oneshot_mods();
    if (mods) {
        rgb_matrix_indicate_modifiers(mods);
    }
}

void rgb_matrix_indiciate_modifiers(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) {
        rgb_matrix_set_color(63, 0xFF, 0xFF, 0x20);
        rgb_matrix_set_color(74, 0xFF, 0xFF, 0x20);
    }
}
#endif