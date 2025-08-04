#include "raw_hid.h"
#include "ddrcode.h"

#define RAW_MSG_LAYER_CHANGE 0x01

static void send_layer_change(layer_state_t state) {
    uint8_t data[32] = {0};
    data[0] = RAW_MSG_LAYER_CHANGE;
    data[1] = get_highest_layer(state);
    raw_hid_send(data, sizeof(data));
}

layer_state_t layer_state_set_user(layer_state_t state) {
    send_layer_change(state);
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    send_layer_change(state);
    return state;
}

