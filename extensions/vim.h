#pragma once

#include <stdint.h>
#include "quantum.h"
#include "helpers/helpers.h"

#define VI_SEQ_SIZE 10

typedef kc_t * const vi_seq_t;

typedef enum {
    NORMAL = 0,
    SELECTION,
    INSERT,
    DELETE,
    JUMP // g-key 
} vi_mode_t;

typedef struct {
    uint16_t rep;
    vi_mode_t mode;
    kc_t keycode;
} vi_cmd_t;

bool is_vi_mode_on(void);
void enter_vi_mode(void);
void exit_vi_mode(void);
void toggle_vi_mode(void);

bool parse_vi_seq(vi_seq_t seq, vi_cmd_t * cmd);
bool process_record_vim(uint16_t keycode, keyrecord_t *record);
bool is_vi_seq_complete(vi_cmd_t * const cmd);
