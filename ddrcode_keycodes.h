#pragma once
#include QMK_KEYBOARD_H

// Use QK_USER_0.. to reserve your userspace range.
enum ddr_keycodes {
    DDR_BL = QK_USER_0,   // 0x7E40
    DDR_CHARON,           // 0x7E41
    DDR_LL,               // 0x7E42
    DDR_WPM,              // 0x7E43
};


