#include "print.h"
#include "ddrcode.h"

static const uint8_t wpm_treshold = 20; // min wpm required to consider actual typing
static const uint32_t wpm_interval = WPM_SAMPLE_SECONDS * 1000;

typedef struct {
    uint8_t current_wpm;
    uint32_t wpm_sum;
    uint32_t wpm_count;
    uint8_t wpm_max;
    const char * layout_name;
} wpmstats_t;

static wpmstats_t wpmstats[] = {
    { 0, 0, 0, 0, "qwerty" }, 
    { 0, 0, 0, 0, "colemak" } 
}; 

static void print_wpm(wpmstats_t const * const stats) {
    printf(
        "WPM stats for %s layout: current WPM: %d, max WPM: %d, avg WPM: %ld (based on %ld minutes of typing)\n",
        stats->layout_name,
        stats->current_wpm,
        stats->wpm_max,
        stats->wpm_sum / stats->wpm_count,
        stats->wpm_count * WPM_SAMPLE_SECONDS / 60);
}

uint32_t wpm_timer(uint32_t trigger_time, void *cb_arg) {
    const uint8_t wpm = get_current_wpm();
    if (wpm >= wpm_treshold) {
        wpmstats_t * const stats = &wpmstats[default_layer_state == 1 << COLEMAK ? 1 : 0]; // default to qwerty when not colemak
        stats->current_wpm = wpm;
        stats->wpm_sum += wpm;
        stats->wpm_count += 1;
        if (wpm > stats->wpm_max)  stats->wpm_max = wpm;
        if (((stats->wpm_count >> 1) & 1) == 0) {
            print_wpm(stats);
        }
    }
    return wpm_interval;
}


void init_wpm(void) {
    defer_exec(wpm_interval, wpm_timer, NULL);
}

