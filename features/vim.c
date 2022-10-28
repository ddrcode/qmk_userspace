#include "vim.h"
#include "print.h"

#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)
#define TAP(keycode) register_code16(keycode); unregister_code16(keycode)
#define REPEAT(CODE) for(int i=state->rep; i; --i) CODE;
#define VI_FN(NAME) void vi_ ## NAME(vi_state_t * const state)
#define FN_CALL(NAME) vi_ ## NAME(&state); break

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
    print("Proccesing del\n");
    REPEAT(TAP(KC_DEL));
}

VI_FN(insert) {
    layer_off(4);
}

VI_FN(left) { REPEAT(TAP(KC_LEFT)); }
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

bool process_record_vim(uint16_t keycode, keyrecord_t *record) {
    static vi_state_t state = { 1, MAC, NORMAL };

    if (get_highest_layer(layer_state) != VIM_LAYER ) return true;
    if (!record->event.pressed) return false;

    printf(" keycode %d  \n", keycode);
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) return true;

    printf("Proccesing vim keycode %d  \n", keycode);

    switch(keycode) {
        case KC_1...KC_9: state.rep = keycode-KC_1+1; break;
        case VI_INSERT: vi_insert(&state); break;
        case VI_DELETE: vi_del(&state); break;
        case VI_UNDO: vi_undo(&state); break;
        case VI_LEFT: vi_left(&state); break;
        case VI_RIGHT: FN_CALL(right);
        case VI_UP: FN_CALL(up);
        case VI_DOWN: FN_CALL(down);
    }

    if (keycode < KC_1 || keycode > KC_9) state.rep = 1;

    return false;
}
