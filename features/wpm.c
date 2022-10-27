#include "quantum.h"
#include "print.h"


static const uint8_t wpm_treshold = 20; // min wpm required to consider actual typing
static const uint32_t wpm_interval = WPM_SAMPLE_SECONDS * 1000;

static uint32_t wpm_sum = 0;
static uint32_t wpm_count = 0;
static uint8_t wpm_max = 0;


uint32_t wpm_timer(uint32_t trigger_time, void *cb_arg) {
    const uint8_t wpm = get_current_wpm();
    if (wpm >= wpm_treshold) {
        wpm_sum += wpm;
        ++wpm_count;
        wpm_max = wpm > wpm_max ? wpm : wpm_max;
        if (((wpm_count >> 1) & 1) == 0) {
            printf("Current WPM: %d, max WPM: %d, avg WPM: %ld (based on %ld minutes of typing)\n", 
                wpm, wpm_max, wpm_sum / wpm_count, wpm_count * WPM_SAMPLE_SECONDS / 60);
        }
    }
    return wpm_interval;
}


void init_wpm(void) {
    defer_exec(wpm_interval, wpm_timer, NULL);
}

