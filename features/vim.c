#include "vim.h"
#include "print.h"

#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)
#define REPEAT(CODE) for(int i=state->rep; i; --i) {CODE;}
#define TAPN(keycode) REPEAT(TAP(keycode))
#define VI_FN(NAME) static void vi_ ## NAME(vi_state_t * const state)
#define FN_CALL(NAME) vi_ ## NAME(state);
#define OS_MOD os_mod(state)
#define MODTAPN(MOD, KC)  PRESS(MOD); TAPN(KC); RELEASE(MOD)

extern bool vi_mode_on;

static inline void TAP(int16_t keycode) {
    register_code16(keycode);
    unregister_code16(keycode);
}

static inline void MODTAP(int16_t mod, int16_t keycode) {
    PRESS(mod);
    TAP(keycode);
    RELEASE(mod);
}


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
    bool shift_down;
    bool ctrl_down;
} vi_state_t;

static inline uint16_t os_mod(vi_state_t * const state) {
    return state->os == MAC ? KC_LEFT_GUI : KC_LEFT_CTRL;
}

static void change_mode(vi_state_t * const state, vi_mode_t mode) {
    if (state->mode == mode) return;
    if (state->mode == SELECTION) TAP(KC_ESC);
    state->mode = mode;
}

static void vi_cut(vi_state_t * const state) {
    MODTAP(os_mod(state), KC_X);
}

VI_FN(reset) {
    state->rep = 1;
    state->ctrl_down = false;
    state->shift_down = false;
    change_mode(state, NORMAL);
    // clear_keyboard();
}

VI_FN(insert) {
    vi_reset(state);
    vi_mode_on = false;
}

VI_FN(append) {
    TAP(KC_RIGHT);
    FN_CALL(insert);
}

VI_FN(del) {
    TAPN(KC_DEL);
}

VI_FN(left) { REPEAT(TAP(KC_LEFT)); }
VI_FN(right) { REPEAT(TAP(KC_RIGHT)); }
VI_FN(up) { REPEAT(TAP(KC_UP)); }
VI_FN(down) { REPEAT(TAP(KC_DOWN)); }

VI_FN(undo) {
    MODTAPN(OS_MOD, KC_Z);
}

VI_FN(redo) {
    if (state->os == MAC) {
        PRESS(KC_LEFT_GUI);
        PRESS(KC_LEFT_SHIFT);
        TAPN(KC_Z);
        RELEASE(KC_LEFT_SHIFT);
        RELEASE(KC_LEFT_GUI);
    } else {
        PRESS(KC_LEFT_CTRL);
        TAPN(KC_Y);
        RELEASE(KC_LEFT_CTRL);
    }
}

VI_FN(bol) {
    TAP(KC_HOME);
    TAP(KC_HOME);
}

VI_FN(eol) {
    TAP(KC_END);    
}

VI_FN(eof) {
    MODTAP(os_mod(state), state->os == MAC ? KC_DOWN : KC_END);
}

VI_FN(del_fn) {
    if (state->mode == NORMAL) {
        change_mode(state, DELETE);
        return;
    }
    vi_bol(&(vi_state_t){ 1, state->os, NORMAL });
    PRESS(KC_LEFT_SHIFT);
    REPEAT(TAP(KC_DOWN));
    RELEASE(KC_LEFT_SHIFT);
    vi_cut(state);
    vi_reset(state);
}

VI_FN(yank) {
    if (state->mode == SELECTION) RELEASE(KC_LEFT_SHIFT);
    MODTAP(OS_MOD, KC_C);
    FN_CALL(reset);
}

VI_FN(paste) {
    MODTAPN(OS_MOD, KC_V);
    vi_reset(state);
}

VI_FN(mod_select) {
    change_mode(state, SELECTION);
    PRESS(KC_LSHIFT);
}

VI_FN(back_word) {
    MODTAPN(state->os == MAC ? KC_LALT : KC_LCTRL, KC_LEFT);
}

VI_FN(new_line) {
    FN_CALL(eol);
    TAPN(KC_ENTER);
    FN_CALL(insert);
}

VI_FN(new_line_up) {
    FN_CALL(bol);
    TAPN(KC_ENTER);
    TAP(KC_UP);
    FN_CALL(insert);
}

VI_FN(join_line) {
    REPEAT(
        FN_CALL(eol);
        TAP(KC_SPACE);
        TAP(KC_DEL);
    );
}

VI_FN(replace_then_edit) {
    MODTAPN(KC_LEFT_SHIFT, KC_RIGHT);
    FN_CALL(cut);
    FN_CALL(insert);
}

__attribute__((weak)) 
uint16_t vi_key_override(uint16_t keycode) {
    switch(keycode) {
        case KC_H: return KC_I;
        case KC_I: return KC_K;
        case KC_J: return KC_H;
        case KC_K: return KC_J;
        case KC_BSLS: return KC_I;
    }
    return keycode;
}

static bool vi_is_layer_key(uint16_t keycode) {
    switch (keycode) {
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            printf("Layer key down %d, %d \n", keycode, keycode & 0xFF);
            return true;
    }
    return  false;
}

static void vi_process_record(uint16_t keycode, vi_state_t * const state) {
    switch(keycode) {
        // repetition
        case KC_1...KC_9: 
        case KC_P1...KC_P9: state->rep = keycode-KC_1+1; break;

        // navigation (hjkl)
        case KC_LEFT:
        case KC_H: FN_CALL(left); break;
        case KC_RIGHT:
        case KC_L: FN_CALL(right); break;
        case KC_UP:
        case KC_K: FN_CALL(up); break;
        case KC_DOWN:
        case KC_J: FN_CALL(down); break;

        // jumps (eb0$G)
        case KC_0: 
        case KC_P0: FN_CALL(bol); break;
        case S(KC_4): FN_CALL(eol); break;
        case KC_B: FN_CALL(back_word); break;
        case KC_E: MODTAP(KC_LALT, KC_RIGHT); break;
        case S(KC_G): FN_CALL(eof); break;

        // edits (aioAIJO)
        case KC_A: FN_CALL(append); break;
        case KC_I: FN_CALL(insert); break;
        case S(KC_A): FN_CALL(eol); FN_CALL(insert); break;
        case S(KC_I): FN_CALL(bol); FN_CALL(insert); break;
        case KC_O: FN_CALL(new_line); break;
        case S(KC_O): FN_CALL(new_line_up); break;
        case KC_S: FN_CALL(replace_then_edit); break;
        case S(KC_J): FN_CALL(join_line); break;
       
        // delete (xXd)
        case KC_D: FN_CALL(del_fn); break;
        case KC_DEL:
        case KC_X: FN_CALL(del);  break;
        case KC_BSPC:
        case S(KC_X): TAPN(KC_BACKSPACE); break;
        
        // copy / paste (yp)
        case KC_P: FN_CALL(paste); break;
        case KC_Y: FN_CALL(yank); break;

        // undo / redo (u)
        case KC_U: FN_CALL(undo); break;
        case C(KC_R): FN_CALL(redo); break;

        // VI modes (v)
        case KC_V: FN_CALL(mod_select); break;
        
        // other (Esc)
        case KC_ESC: FN_CALL(reset); break;
    }

    if (keycode < KC_1 || keycode > KC_9) state->rep = 1;
}

static uint16_t vi_process_mods(uint16_t keycode, bool pressed) {
    static bool shift_down = false;
    static bool ctrl_down = false;

    if (IS_MOD(keycode)) {
        switch (keycode) {
            case KC_LEFT_SHIFT:
            case KC_RIGHT_SHIFT:
                shift_down = pressed;
                break;
            case KC_LEFT_CTRL:
            case KC_RIGHT_CTRL:
                ctrl_down = pressed;
                break;
        }
    }
    if (ctrl_down) keycode |= 1 << 8;
    if (shift_down) keycode |= 2 << 8;
    return keycode;
}

bool process_record_vim(uint16_t keycode, keyrecord_t *record) {
    static vi_state_t state = { 1, MAC, NORMAL, false, false };

    if (vi_is_layer_key(keycode)) return true;
    keycode = vi_process_mods(keycode, record->event.pressed);

    if (!record->event.pressed) return false;

    keycode = vi_key_override(keycode);
    printf("QMK state: rep=%d, mode=%d, kc=%d (%d, %d), shift=%d, ctrl=%d\n", state.rep, state.mode, keycode, keycode & 0xff, keycode >> 8, state.shift_down, state.ctrl_down);

    vi_process_record(keycode, &state);
    return false;
}
