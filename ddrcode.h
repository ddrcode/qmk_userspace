#pragma once

#include "quantum.h"
#include "action.h"
#include "version.h"

#ifdef CONSOLE_ENABLE
#include "features/debug.h"
#endif

enum layerNames { QWERTY, COLEMAK, DEFAULT, SYMBOLS, NAVIGATION };

bool vi_mode_on = false;