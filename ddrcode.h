#pragma once

#include "quantum.h"
#include "action.h"
#include "version.h"

#ifdef CONSOLE_ENABLE
#include "features/debug.h"
#endif

enum layerNames { QWERTY, COLEMAK, DEFAULT, SYMBOLS, NAVIGATION };

enum custom_keycodes {
  KC_MAKE = SAFE_RANGE,
  NEW_SAFE_RANGE  //use "NEW_SAFE_RANGE" for keymap specific codes
};

#ifdef KEY_OVERRIDE_ENABLE
// Declare the key overrides array that will be defined in key_overrides.c
extern const key_override_t *key_overrides[];
#endif
