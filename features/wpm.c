#include "quantum.h"
#include "print.h"

static const uint32_t wpm_interval = 10000;

uint32_t wpm_timer(uint32_t trigger_time, void *cb_arg) {
    const uint8_t wpm = get_current_wpm();
    if (wpm > 0) printf("Current WPM: %d\n", wpm);
    return wpm_interval;
}

void init_wpm(void) {
    defer_exec(wpm_interval, wpm_timer, NULL);
}

