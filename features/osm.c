#include "quantum.h"

static uint8_t osm_tap = 0; 

void oneshot_mods_changed_user(uint8_t mods) {
    osm_tap &= mods;
}

bool process_record_user_osm(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    if (keycode & QK_ONE_SHOT_MOD) {
        uint8_t mod = keycode & ~QK_ONE_SHOT_MOD;
        if (mod & 0b00010000) mod <<= 4;  // handle r-modifiers
        if (record->tap.count > 1) {
            osm_tap &= ~mod;
            return true;
        }
        if (osm_tap & mod) {
            del_oneshot_mods(mod);
            osm_tap &= ~mod;
            return false;
        }
        osm_tap |= mod;
    } else {
        osm_tap = 0;
    }
    
    return true;
}


