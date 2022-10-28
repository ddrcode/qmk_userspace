#pragma once

#define VIM_LAYER   4

#define DDR_VI(x)   DDR_KC(100+x)

#define VI_ESC      DDR_VI(0)

#define VI_APPEND   DDR_VI(1)
#define VI_INSERT   DDR_VI(2)
#define VI_DELETE   DDR_VI(3)
#define VI_UNDO     DDR_VI(4)
#define VI_REDO     DDR_VI(5)

#define VI_UP       DDR_VI(20)
#define VI_DOWN     DDR_VI(21)
#define VI_LEFT     DDR_VI(22)
#define VI_RIGHT    DDR_VI(23)

#define VI_DELFN    DDR_VI(40)
