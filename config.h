#pragma once

/* Custom keycodes */

#define DDR_KEY(idx)   (4096+idx)

#define CKC_SEC1    DDR_KEY(0)
#define CKC_SEC2    DDR_KEY(1)
#define CKC_SEC3    DDR_KEY(2)
#define CKC_BL      DDR_KEY(3)
#define CKC_WPM     DDR_KEY(4)
#define CKC_LL      DDR_KEY(5)


/* Optimizations the reduce memory usage */

#ifndef DDR_BIG_MEMORY
    #define LAYER_STATE_8BIT         // alow max 8 layers
    #define NO_ACTION_MACRO          // no macros
    #define NO_ACTION_FUNCTION       // no functions
    #undef LOCKING_SUPPORT_ENABLE    // don't use it if you have cherry MX lock switches
    #undef LOCKING_RESYNC_ENABLE
#endif


/* Disable RGB animations */




#include "wrappers.h"
