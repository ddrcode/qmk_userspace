#include "ddrcode.h"
#include "print.h"

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

void init_wpm(void);


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case CKC_BL:
                uprintf("Hitting CKC_BL %d, %d, %d", default_layer_state, QWERTY, COLEMAK);
                default_layer_set((default_layer_state & QWERTY) ? (1 << COLEMAK) : (1 << QWERTY));
                break;
            case CKC_WPM:
#ifdef WPM_ENABLE
                itoa(get_current_wpm(), wpm_buff, 10);
                SEND_STRING(wpm_buff);
#endif
                break;
#ifdef DDR_BIG_MEMORY  
            case CKC_LL:
                SEND_STRING("ls -al\n");
                break;
#endif
        }
    }

    return process_record_user_osm(keycode, record)
           && process_secrets(keycode, record)
           && process_record_keymap(keycode, record);
}

void keyboard_post_init_user(void) {
    #ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
    #endif

    #ifdef WPM_ENABLE
    init_wpm();
    #endif
}

