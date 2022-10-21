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
