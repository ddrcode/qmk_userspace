#pragma once

#include "quantum.h"

void charon_send_layer_change(layer_state_t state, bool is_default);
void charon_send_key_event(uint16_t keycode, keyrecord_t *record);
void charon_send_keyboard_info(void);
void charon_send_layer_chunk(uint8_t layer, uint16_t offset);
void charon_send_mode_change(uint8_t mode);
void charon_send_mode_toggle(void);

void charon_raw_hid_receive(uint8_t *data, uint8_t len);

