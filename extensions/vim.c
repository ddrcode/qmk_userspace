#include "vim.h"
#include "helpers/helpers.h"
#include "print.h"

#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)
#define REPEAT(CODE) for(int i=cmd->rep; i; --i) {CODE;}
#define TAP(keycode) tap_code16(keycode)
#define TAPN(keycode) REPEAT(TAP(keycode))
#define VI_FN(NAME) static void vi_ ## NAME(vi_cmd_t * const cmd)
#define FN_CALL(NAME) vi_ ## NAME(cmd);
#define OS_MOD os_mod()
#define MODTAPN(MOD, KC)  PRESS(MOD); TAPN(KC); RELEASE(MOD)

static void vi_exec_cmd(vi_cmd_t * const cmd);

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

typedef struct {
    op_system_t os;
    vi_mode_t mode;
    bool shift_down;
    bool ctrl_down;
    vi_cmd_t last_cmd;
} vi_state_t;

bool vi_mode_on = false;

static vi_state_t state = { MAC, VI_NORMAL_MODE, false, false };
static kc_t vi_seq[VI_SEQ_SIZE];

static inline uint16_t os_mod(void) {
    return state.os == MAC ? KC_LEFT_GUI : KC_LEFT_CTRL;
}

static void change_mode(vi_mode_t mode) {
    if (state.mode == mode) return;
    if (state.mode == VI_SELECTION_MODE) TAP(KC_ESC);
    state.mode = mode == VI_SELECTION_MODE ? mode : VI_NORMAL_MODE;
}

static void vi_cut(void) {
    MODTAP(os_mod(), KC_X);
}

static void clear_vi_seq(void) {
    for (uint8_t i=0; i<VI_SEQ_SIZE; ++i) {
        vi_seq[i] = 0;
    }
}

void vi_reset(void) {
    state.ctrl_down = false;
    state.shift_down = false;
    change_mode(VI_NORMAL_MODE);
    clear_vi_seq();
    // clear_keyboard();
}

VI_FN(insert) {
    vi_reset();
    exit_vi_mode();
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
    if (state.os == MAC) {
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
    if (is_kc_zero(cmd->keycode)) TAP(KC_HOME);
}

VI_FN(eol) {
    TAP(KC_END);    
}

VI_FN(bof) {
    MODTAP(os_mod(), state.os == MAC ? KC_UP : KC_HOME);
}

VI_FN(eof) {
    MODTAP(os_mod(), state.os == MAC ? KC_DOWN : KC_END);
}

VI_FN(del_line) {
    if (cmd->mode != VI_DELETE_MODE) return;
    vi_bol(&(vi_cmd_t){ 1, VI_NORMAL_MODE, KC_0 });
    PRESS(KC_LEFT_SHIFT);
    REPEAT(TAP(KC_DOWN));
    RELEASE(KC_LEFT_SHIFT);
    vi_cut();
    vi_reset();
}

VI_FN(yank) {
    if (state.mode == VI_SELECTION_MODE) RELEASE(KC_LEFT_SHIFT);
    MODTAP(OS_MOD, KC_C);
    vi_reset();
}

VI_FN(paste) {
    MODTAPN(OS_MOD, KC_V);
    vi_reset();
}

VI_FN(mod_select) {
    change_mode(VI_SELECTION_MODE);
    PRESS(KC_LSHIFT);
}

VI_FN(back_word) {
    MODTAPN(state.os == MAC ? KC_LALT : KC_LCTRL, KC_LEFT);
}

VI_FN(forward_word) {
    MODTAPN(state.os == MAC ? KC_LALT : KC_LCTRL, KC_RIGHT);
}

VI_FN(forward_next_word) {
    FN_CALL(forward_word);
    TAP(KC_RIGHT);
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
        if (cmd->mode == VI_NORMAL_MODE) TAP(KC_SPACE);
        TAP(KC_DEL);
    );
}

VI_FN(replace_then_edit) {
    MODTAPN(KC_LEFT_SHIFT, KC_RIGHT);
    vi_cut();
    FN_CALL(insert);
}

VI_FN(exec_last) {
    REPEAT(vi_exec_cmd(&state.last_cmd));
}

__attribute__((weak)) 
kc_t vi_key_override(kc_t keycode) {
    return keycode;
}

static kc_t vi_process_mods(kc_t keycode, bool pressed) {
    if (IS_MOD(keycode)) {
        switch (keycode) {
            case KC_LEFT_SHIFT:
            case KC_RIGHT_SHIFT:
                state.shift_down = pressed;
                break;
            case KC_LEFT_CTRL:
            case KC_RIGHT_CTRL:
                state.ctrl_down = pressed;
                break;
        }
    }
    if (state.ctrl_down) keycode |= 1 << 8;
    if (state.shift_down) keycode |= 2 << 8;
    return keycode;
}

static void vi_handle_mode(vi_cmd_t * const cmd, bool before_cmd) {
    vi_mode_t mode = cmd->mode;
    if ((mode == VI_CHANGE_MODE || mode == VI_DELETE_MODE || mode == VI_YANK_MODE) && mode != kc2mode(cmd->keycode)) {
        if (before_cmd) PRESS(KC_LEFT_SHIFT);
        else RELEASE(KC_LEFT_SHIFT);
    }
}

static void vi_exec_cmd(vi_cmd_t * const cmd) {
    vi_handle_mode(cmd, true);

    switch (cmd->keycode) {

        // navigation (hjkl)
        case KC_LEFT:
        case KC_H: FN_CALL(left); break;
        case KC_RIGHT:
        case KC_L: FN_CALL(right); break;
        case KC_UP:
        case KC_K: FN_CALL(up); break;
        case KC_DOWN:
        case KC_J: FN_CALL(down); break;

        // jumps (eb0$G_^)
        case KC_0: 
        case KC_P0: 
        case S(KC_6):
        case S(KC_MINUS): FN_CALL(bol); break;
        case S(KC_4): FN_CALL(eol); break;
        case KC_B: FN_CALL(back_word); break;
        case KC_E: FN_CALL(forward_word); break;
        case KC_W: FN_CALL(forward_next_word); break;
        case KC_G: if (cmd->mode == VI_JUMP_MODE) FN_CALL(bof); break;
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
       
        // delete (xXdC)
        case KC_D: FN_CALL(del_line); break;
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
        
        // other (.)
        case KC_DOT: FN_CALL(exec_last); break;
    }

    if (cmd->mode > 0) {
        vi_handle_mode(cmd, false);
        switch(cmd->mode) {
            case VI_YANK_MODE:
                MODTAP(OS_MOD, KC_C);
                TAP(KC_ESC);
                break;

            case VI_DELETE_MODE:
                vi_cut();
                break;

            case VI_CHANGE_MODE:
                vi_cut();
                exit_vi_mode();
                break;

            default: break;
        }
    }
}

static void process_vi_seq(kc_t keycode) {
    if (!is_kc_printable_char(keycode & 0xff) && !is_kc_arrow(keycode & 0xff)) return;
    if (keycode == KC_ESC) {
        vi_reset();
        return;
    }

    uint8_t i = 0;
    while (i<VI_SEQ_SIZE && vi_seq[i++] > 0);
    vi_seq[--i] = keycode;
    vi_cmd_t cmd = (vi_cmd_t){ .rep=1, .mode=VI_NORMAL_MODE, .keycode=0 };
    if (!parse_vi_seq(vi_seq, &cmd)) {
        clear_vi_seq();
        if (i > 0) process_vi_seq(keycode);
    }
    else if (is_vi_seq_complete(&cmd)) {
        printf("CMD is complete rep=%d, keycode=%d, mode=%d\n", cmd.rep, cmd.keycode, cmd.mode);
        change_mode(cmd.mode);
        vi_exec_cmd(&cmd);
        if (cmd.keycode != KC_DOT) state.last_cmd = cmd;
        clear_vi_seq();
    }
}

bool process_record_vim(uint16_t keycode, keyrecord_t *record) {
    if (is_layer_key(keycode)) return true;
    keycode = vi_process_mods(keycode, record->event.pressed);

    if (!record->event.pressed) return false;

    keycode = vi_key_override(keycode);

    process_vi_seq(keycode);
    return false;
}

void enter_vi_mode(void) {
    clear_keyboard();
    vi_reset();
    vi_mode_on = true;
}

void exit_vi_mode(void) {
    vi_mode_on = false;
    vi_reset();
}

void toggle_vi_mode(void) {
    if (vi_mode_on) exit_vi_mode();
    else enter_vi_mode();
}

bool is_vi_mode_on(void) {
    return vi_mode_on;
}

