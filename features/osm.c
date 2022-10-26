#include "quantum.h"

/**
 * This customization of OSM functionality adds the following features:
 * 1. Option to switch off OSM modifier, by pressing 2nd time on the same key
 * 2. It treats left and right shift, ctrl and gui keys equally, but
 *    it differentiates between Alt keys (left Alt vs AltGr)
 */

/**
 * Holds the flags of previously tapped modifiers. 
 * Bit fields (left-to-right)
 * 7: AltGr (Right Alt)
 * 6: Unused
 * 5: Unused
 * 4: Unused
 * 3: Left Alt
 * 2: Gui (Left or right)
 * 1: Shift (Left or right)
 * 0: Ctrl (Left or right)
 */
static uint8_t osm_tap_flags = 0;

static const uint8_t tapflags_mask = 0b10001111;


static uint8_t keycode2tapflags(uint16_t keycode) {
    const uint8_t mod = keycode & ~QK_ONE_SHOT_MOD;
    if (mod & 0b00010000) { // r-modifiers
        if (mod & 0b10000000) return 0b10000000; // AltGr
        return mod & 0b00001111;
    }
    return mod;
}


static uint8_t osmmods2tapflags(uint8_t mods) {
    return (mods & tapflags_mask) | ((mods & ~tapflags_mask) >> 4);
}


void oneshot_mods_changed_user(uint8_t mods) {
    osm_tap_flags &= osmmods2tapflags(mods);
}


bool process_record_user_osm(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    if (keycode & QK_ONE_SHOT_MOD) {
        const uint8_t mod = keycode2tapflags(keycode);
        if (record->tap.count > 1) {
            osm_tap_flags &= ~mod;
            return true;
        }
        if (osm_tap_flags & mod) {
            del_oneshot_mods(mod | ((mod << 4) & ~tapflags_mask));
            osm_tap_flags &= ~mod;
            return false;
        }
        osm_tap_flags |= mod;
    } else {
        osm_tap_flags = 0;
    }
    
    return true;
}

