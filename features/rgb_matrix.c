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
void rgb_matrix_indiciate_modifiers(uint8_t mods, uint8_t led_min, uint8_t led_max);
static inline uint8_t modmask_for_kc(uint16_t kc);


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
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

    const uint8_t mods = get_mods() | get_oneshot_mods();
    if (mods) {
        rgb_matrix_indiciate_modifiers(mods, led_min, led_max);
    }

    return false;
}

void rgb_matrix_indiciate_modifiers(uint8_t mods, uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index == NO_LED || led_index < led_min || led_index > led_max) continue;

            // ✅ correct order: { .row = row, .col = col }
            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){ .row = row, .col = col });

            // highlight only if this position is a *modifier key* and that mod is currently active
            uint8_t need = modmask_for_kc(kc);
            if (need && (mods & need)) {
                rgb_matrix_set_color(led_index, RGB_GREEN);
            }
        }
    }
}

static inline uint8_t modmask_for_kc(uint16_t kc) {
    switch (kc) {
        case KC_LCTL: return MOD_BIT(KC_LCTL);
        case KC_RCTL: return MOD_BIT(KC_RCTL);
        case KC_LSFT: return MOD_BIT(KC_LSFT);
        case KC_RSFT: return MOD_BIT(KC_RSFT);
        case KC_LGUI: return MOD_BIT(KC_LGUI);
        case KC_RGUI: return MOD_BIT(KC_RGUI);
        case KC_LALT: return MOD_BIT(KC_LALT);
        case KC_RALT: return MOD_BIT(KC_RALT);
        default: break;
    }
    // Treat mod-tap as its modifier role for highlighting
    if (IS_QK_MOD_TAP(kc)) {
        uint8_t m = (uint8_t)(kc & 0xFF);           // low byte carries mods
        // normalize L/R pairs to full masks
        uint8_t out = 0;
        if (m & MOD_MASK_CTRL)  out |= MOD_MASK_CTRL;
        if (m & MOD_MASK_SHIFT) out |= MOD_MASK_SHIFT;
        if (m & MOD_MASK_GUI)   out |= MOD_MASK_GUI;
        if (m & MOD_BIT(KC_LALT)) out |= MOD_BIT(KC_LALT);
        if (m & MOD_BIT(KC_RALT)) out |= MOD_BIT(KC_RALT);
        return out;
    }
    if (IS_QK_ONE_SHOT_MOD(kc)) {
        return (uint8_t)(kc & 0xFF);
    }
    return 0;
}

#endif
