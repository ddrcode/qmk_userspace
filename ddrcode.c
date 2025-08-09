#include "ddrcode.h"
#include "ddrcode_keycodes.h"
#include "print.h"
#include "features/charon.h"
#include "features/wpm.h"

#ifdef WPM_ENABLE
char wpm_buff[5];
#endif

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

__attribute__((weak)) bool process_secrets(uint16_t keycode, keyrecord_t *record) {
    return true;
}

__attribute__((weak)) bool process_record_user_osm(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    charon_send_key_event(keycode, record);

    bool pressed = record->event.pressed;
    switch (keycode) {
        case KC_F20:
        case DDR_BL:
            if (pressed) {
                uprintf("Hitting DDR_BL %d, %d, %d", default_layer_state, QWERTY, COLEMAK);
                default_layer_set((default_layer_state & QWERTY) ? (1 << COLEMAK) : (1 << QWERTY));
            }
            return false;

        case KC_F21:
#ifdef RAW_ENABLE
        case DDR_CHARON:
            if (pressed) charon_send_mode_toggle();
#endif
            return false;

        case KC_F22:
#ifdef DDR_BIG_MEMORY
        case DDR_LL:
            if (pressed) SEND_STRING("ls -al\n");
#endif

            return false;

        case KC_F23:
#ifdef WPM_ENABLE
        case DDR_WPM:
            if (pressed) {
                itoa(get_current_wpm(), wpm_buff, 10);
                SEND_STRING(wpm_buff);
            }
#endif
            return false;

    }

    return process_record_user_osm(keycode, record)
           && process_secrets(keycode, record)
           && process_record_keymap(keycode, record);
}

void keyboard_post_init_user(void) {
    // Key overrides are automatically initialized by QMK

    #ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
    #endif

    #ifdef WPM_ENABLE
    init_wpm();
    #endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    charon_send_layer_change(state, false);
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    charon_send_layer_change(state, true);
    return state;
}

void raw_hid_receive(uint8_t *data, uint8_t len) {
    charon_raw_hid_receive(data, len);
}
