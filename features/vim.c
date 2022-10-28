#include "quantum.h"

#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)
#define TAP(keycode) register_code16(keycode); unregister_code16(keycode)
#define REPEAT(N, CODE) for(int i=N; i; --i) CODE;
#define VI_FN(NAME) void vi_NAME(const uint8_t rep, const op_system_t sys, vi_mode_t mode)

typedef enum OpSystems {
    UNKNOWN,
    LINUX_TERM,
    LINUX_GUI,
    MAC,
    WIN
} op_system_t;

typedef enum {
    NORMAL,
    SELECTION,
    INSERT
} vi_mode_t;


VI_FN(del) {
     REPEAT(rep, TAP(KC_DEL));
}
