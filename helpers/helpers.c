#include "helpers.h"
#include "ddrcode.h"

bool is_default_layer_colemak(void) {
    return get_highest_layer(default_layer_state) == COLEMAK;
}

bool is_default_layer_qwerty(void) {
    return get_highest_layer(default_layer_state) == QWERTY;
}

