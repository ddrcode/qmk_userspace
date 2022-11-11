#pragma once

#include <stdint.h>
#include "quantum.h"
#include "helpers/helpers.h"

typedef kc_t * const vi_seq_t;

typedef struct {
    uint16_t rep;
    uint8_t mode;
    kc_t cmd;
} vi_cmd_t;

typedef enum {
    NORMAL,
    SELECTION,
    INSERT,
    DELETE
} vi_mode_t;

bool parse_vi_seq(vi_seq_t seq, vi_cmd_t * cmd);
bool process_record_vim(uint16_t keycode, keyrecord_t *record);