#pragma once

#include <stdbool.h>
#include <stdint.h>

// types

typedef uint16_t kc_t;


// layers

bool is_default_layer_colemak(void);
bool is_default_layer_qwerty(void);


// keycodes

bool is_kc_in_range(kc_t keycode, kc_t from, kc_t to);
bool is_layer_key(kc_t keycode);
bool is_kc_digit(kc_t kc);
bool is_kc_zero(kc_t kc);
uint8_t kc2digit(kc_t kc);
bool is_kc_printable_char(kc_t keycode);
bool is_kc_arrow(kc_t keycode);


// math

uint16_t int_pow10(uint8_t x);
