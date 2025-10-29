/**
 * This customization of OSM functionality adds the following features:
 * 1. Option to switch off OSM modifier, by pressing 2nd time on the same key
 * 2. It treats left and right shift, ctrl and gui keys equally, but
 *    it differentiates between Alt keys (left Alt vs AltGr)
 */

#include QMK_KEYBOARD_H

// Group flags for our local “armed” OSM toggles
enum {
    OSMG_CTRL  = (1 << 0),
    OSMG_SHIFT = (1 << 1),
    OSMG_GUI   = (1 << 2),
    OSMG_LALT  = (1 << 3),
    OSMG_RALT  = (1 << 7),
};
static uint8_t osm_groups_armed = 0;

/* Map an OSM keycode to:
 *  - a group bit (our local toggle bucket)
 *  - the actual QMK 8-bit mod mask to add/remove
 * Returns group_bit=0 when the keycode isn’t an OSM we care about.
 */
static void osm_keycode_to_group_and_mask(uint16_t keycode, uint8_t *group_bit, uint8_t *mask8) {
    *group_bit = 0;
    *mask8     = 0;

    if (keycode < QK_ONE_SHOT_MOD || keycode > QK_ONE_SHOT_MOD_MAX) return;

    // OSM encodes its modifier mask in the low byte — use official masks, no guessing.
    const uint8_t m = (uint8_t)(keycode & 0xFF);

    if (m & MOD_MASK_CTRL)   { *group_bit = OSMG_CTRL;  *mask8 = MOD_MASK_CTRL;  return; }
    if (m & MOD_MASK_SHIFT)  { *group_bit = OSMG_SHIFT; *mask8 = MOD_MASK_SHIFT; return; }
    if (m & MOD_MASK_GUI)    { *group_bit = OSMG_GUI;   *mask8 = MOD_MASK_GUI;   return; }
    if (m & MOD_BIT(KC_LALT)){ *group_bit = OSMG_LALT;  *mask8 = MOD_BIT(KC_LALT); return; }
    if (m & MOD_BIT(KC_RALT)){ *group_bit = OSMG_RALT;  *mask8 = MOD_BIT(KC_RALT); return; }
}

/* Keep our local “armed” flags in sync if something else changes oneshot mods. */
void oneshot_mods_changed_user(uint8_t mods) {
    osm_groups_armed = 0;
    if (mods & MOD_MASK_CTRL)    osm_groups_armed |= OSMG_CTRL;
    if (mods & MOD_MASK_SHIFT)   osm_groups_armed |= OSMG_SHIFT;
    if (mods & MOD_MASK_GUI)     osm_groups_armed |= OSMG_GUI;
    if (mods & MOD_BIT(KC_LALT)) osm_groups_armed |= OSMG_LALT;
    if (mods & MOD_BIT(KC_RALT)) osm_groups_armed |= OSMG_RALT;
}

/* Call from process_record_user() BEFORE other consumers. */
bool process_record_user_osm(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    // Non-OSM key: commit/clear pending armed state (let QMK handle normal OSM behavior)
    if (keycode < QK_ONE_SHOT_MOD || keycode > QK_ONE_SHOT_MOD_MAX) {
        osm_groups_armed = 0;
        return true;
    }

    uint8_t group_bit = 0, mask8 = 0;
    osm_keycode_to_group_and_mask(keycode, &group_bit, &mask8);
    if (!group_bit) return true;  // unknown/unhandled OSM → let stock behavior run

    // Don’t toggle on multi-tap; let QMK’s tap-toggle/timeouts do their thing
    if (record->tap.count > 1) {
        osm_groups_armed &= ~group_bit;
        return true;
    }

    // If this group is already armed (e.g., you pressed the other side), pressing any member cancels it
    if (osm_groups_armed & group_bit) {
        del_oneshot_mods(mask8);       // remove those OSM mods (full 8-bit mask)
        osm_groups_armed &= ~group_bit;
        return false;                  // we handled it; don’t pass the key on
    }

    // First tap for this group: arm it and let stock OSM add the mod
    osm_groups_armed |= group_bit;
    return true;
}

