AUDIO_ENABLE = no
TAP_DANCE_ENABLE = no
KEY_LOCK_ENABLE = no
AUTO_SHIFT_ENABLE = no
CAPS_WORD_ENABLE = no
SEND_STRING_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
# BOOTMAGIC_ENABLE = no
# TERMINAL_ENABLE = yes

$(info [ddrcode/rules.mk] start for keyboard: $(strip $(KEYBOARD)))

ifneq ($(filter $(strip $(KEYBOARD)),converter/usb_usb/hasu idobao/id75/v1),)
    # settings for boards with 32kB of RAM
    $(info [ddrcode/rules.mk] applying ram<=32kB settings)
    MOUSEKEY_ENABLE = no
    POINTING_DEVICE_ENABLE = no
else
    # settings for boards with more RAM
    $(info [ddrcode/rules.mk] applying ram>32kB settings)
    WPM_ENABLE = yes
    EXTRAKEY_ENABLE = yes
    CONSOLE_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)),keychron/q10/q10_ansi_stm32l432_ec11)
    # settings for boards with encoder
    $(info [ddrcode/rules.mk] applying encoder settings)
    ENCODER_ENABLE = yes
    ENCODER_MAP_ENABLE = no
endif

SRC += ddrcode.c

$(info [ddrcode/rules.mk] end)
