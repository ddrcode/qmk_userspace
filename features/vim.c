#include "vim.h"
#include "print.h"

#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)
#define TAP(keycode) register_code16(keycode); unregister_code16(keycode)
#define REPEAT(CODE) for(int i=state->rep; i; --i) {CODE;}
#define TAPN(keycode) REPEAT(TAP(keycode))
#define VI_FN(NAME) static void vi_ ## NAME(vi_state_t * const state)
#define FN_CALL(NAME) vi_ ## NAME(state); break


typedef enum {
    UNKNOWN,
    LINUX_TERM,
    LINUX_GUI,
    MAC,
    WIN
} op_system_t;

typedef enum {
    NORMAL,
    SELECTION,
    INSERT,
    DELETE
} vi_mode_t;

typedef struct {
    uint16_t rep;
    op_system_t os;
    vi_mode_t mode;
} vi_state_t;

static inline uint16_t os_mod(vi_state_t * const state) {
    return state->os == MAC ? KC_LEFT_GUI : KC_LEFT_CTRL;
}

static void vi_cut(vi_state_t * const state) {
    PRESS(os_mod(state));
    TAP(KC_X);
    RELEASE(os_mod(state));
}

VI_FN(del) {
    REPEAT(TAP(KC_DEL));
}

// VI_FN(left) { REPEAT(TAP(KC_LEFT)); }
VI_FN(right) { REPEAT(TAP(KC_RIGHT)); }
VI_FN(up) { REPEAT(TAP(KC_UP)); }
VI_FN(down) { REPEAT(TAP(KC_DOWN)); }

VI_FN(undo) {
    uint16_t mod = os_mod(state);
    PRESS(mod);
    REPEAT(TAP(KC_Z));
    RELEASE(mod);
}

VI_FN(bol) {
    TAP(KC_HOME);
    TAP(KC_HOME);
}

VI_FN(eol) {
    TAP(KC_END);    
}

VI_FN(del_fn) {
    if (state->mode == NORMAL) {
        state->mode = DELETE;
        return;
    }
    vi_bol(&(vi_state_t){ 1, state->os, NORMAL });
    PRESS(KC_LEFT_SHIFT);
    REPEAT(TAP(KC_DOWN));
    RELEASE(KC_LEFT_SHIFT);
    vi_cut(state);
}

bool is_vi_key(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) 
     || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) 
     || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) 
        return false;
    return true;
}

uint16_t vi_key_override(uint16_t keycode) {
    switch(keycode) {
        case KC_H: return KC_I;
        case KC_I: return KC_K;
        case KC_J: return KC_H;
        case KC_K: return KC_J;
    }
    return keycode;
}

static bool vi_process_record(uint16_t keycode, vi_state_t * const state) {
    switch(keycode) {
        case KC_1...KC_9: state->rep = keycode-KC_1+1; break;
        case KC_D: FN_CALL(del_fn);
        case KC_LEFT:
        case KC_H: TAPN(KC_LEFT); break;
        case KC_I: TAP(CKC_VI); break;
        case KC_DOWN:
        case KC_J: FN_CALL(down);
        case KC_UP:
        case KC_K: FN_CALL(up);
        case KC_RIGHT:
        case KC_L: FN_CALL(right);
        case KC_U: FN_CALL(undo); 
        case KC_X: FN_CALL(del); 
        default: return true;
    }

    if (keycode < KC_1 || keycode > KC_9) state->rep = 1;
    return false;
}

static bool vi_process_shifted_record(uint16_t keycode, vi_state_t * const state) {
    switch(keycode) {
        case KC_4: FN_CALL(eol);
        case KC_X: TAPN(KC_BACKSPACE); break;
        default: return true;
    }
    return false;
}

bool process_record_vim(uint16_t keycode, keyrecord_t *record) {
    static vi_state_t state = { 1, MAC, NORMAL };

    if (!is_vi_key(keycode)) return true;
    if (!record->event.pressed) return false;

    // printf(" keycode %d  \n", keycode);

    // printf("Proccesing vim keycode %d  \n", keycode);
    const bool shifted = (keyboard_report->mods & MOD_BIT(KC_LSFT)) | (keyboard_report->mods & MOD_BIT(KC_RSFT));
    keycode = vi_key_override(keycode);

    return shifted ? vi_process_shifted_record(keycode, &state) : vi_process_record(keycode, &state);
}
