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


// keycode encodes mods on 5 bits. Convertion to osm_tap_flags
static uint8_t keycode2tapflags(uint16_t keycode) {
    const uint8_t mod = keycode & 0x1f; // modifier flags only (last 5 bits)
    if (mod == 0b00011000) return 0b10000000; // AltGr
    return mod & 0b00001111; // all other modifiers
}


// OSM callback encodes mods on 8 bits. Convertion to osm_tap_flags
static uint8_t osmmods2tapflags(uint8_t osmmods) {
    return (osmmods & tapflags_mask) | ((osmmods & ~tapflags_mask) >> 4);
}


// Required for cases when OSM state changes programatically
void oneshot_mods_changed_user(uint8_t mods) {
    osm_tap_flags &= osmmods2tapflags(mods);
}


// to be invoked from process_record_user function (see ddrcode.c)
bool process_record_user_osm(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    // reset state on non-OSM key press
    if (keycode <= QK_ONE_SHOT_MOD || keycode > QK_ONE_SHOT_MOD_MAX) {
        osm_tap_flags = 0;
        return true;
    }

    const uint8_t mod = keycode2tapflags(keycode);

    // dont toggle on multi-tap
    if (record->tap.count > 1) {
        osm_tap_flags &= ~mod;
        return true;
    }

    // toggle if flag is present and stop tap processing
    if (osm_tap_flags & mod) {
        del_oneshot_mods(mod | ((mod << 4) & ~tapflags_mask));
        osm_tap_flags &= ~mod;
        return false;
    }

    // first OSM tap - set the flag and continue
    osm_tap_flags |= mod;   
    return true;
}

