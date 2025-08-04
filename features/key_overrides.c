#include "quantum.h"
#include "action.h"
#include "ddrcode.h"

#if defined(KEY_OVERRIDE_ENABLE)

// Define key overrides for Colemak layer
const key_override_t ctrl_s_colemak_override = ko_make_with_layers(MOD_MASK_CTRL, KC_R, C(KC_S), (1 << COLEMAK));
const key_override_t cmd_s_colemak_override  = ko_make_with_layers(MOD_MASK_GUI, KC_R, G(KC_S), (1 << COLEMAK));
const key_override_t ctrl_f_colemak_override = ko_make_with_layers(MOD_MASK_CTRL, KC_T, C(KC_F), (1 << COLEMAK));
const key_override_t cmd_f_colemak_override  = ko_make_with_layers(MOD_MASK_GUI, KC_T, G(KC_F), (1 << COLEMAK));

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &ctrl_s_colemak_override,
    &cmd_s_colemak_override,
    &ctrl_f_colemak_override,
    &cmd_f_colemak_override,
    NULL
};

#endif
