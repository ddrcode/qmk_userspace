AUDIO_ENABLE = no
TAP_DANCE_ENABLE = no
KEY_LOCK_ENABLE = no
AUTO_SHIFT_ENABLE = no
CAPS_WORD_ENABLE = no
SEND_STRING_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
# BOOTMAGIC_ENABLE = no
# TERMINAL_ENABLE = yes

ENCODER_ENABLE = no
ENCODER_MAP_ENABLE = no

# settings not for 32kb RAM keyboards
ifneq ($(filter $(strip $(KEYBOARD)),"converter/usb_usb/hasu" "idobao/id75/v1"),)
WPM_ENABLE = yes
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = yes
else
MOUSEKEY_ENABLE = no
POINTING_DEVICE_ENABLE = no
endif

SRC += ddrcode.c
