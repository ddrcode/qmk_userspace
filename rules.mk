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
    CONSOLE_ENABLE = no
    EXTRAKEY_ENABLE = no
    SPACE_CADET_ENABLE = no
    GRAVE_ESC_ENABLE = no 
    MAGIC_ENABLE = no
    EXTRAFLAGS += -flto
else
    # settings for boards with more RAM
    $(info [ddrcode/rules.mk] applying ram>32kB settings)
    WPM_ENABLE = yes
    EXTRAKEY_ENABLE = yes
    CONSOLE_ENABLE = yes
    DDR_BIG_MEMORY = yes
endif

SRC += ddrcode.c

ifeq ($(strip $(KEYBOARD)),keychron/q10/q10_ansi_stm32l432_ec11)
    # settings for boards with encoder
    $(info [ddrcode/rules.mk] applying encoder settings)
    ENCODER_ENABLE = yes
    ENCODER_MAP_ENABLE = no
    SRC += features/encoder.c
endif

ifneq ("$(wildcard $(USER_PATH)/features/secrets.c)", "")
    $(info [ddrcode/rules.mk] including secrets.c)
	SRC += features/secrets.c
endif

ifeq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
    $(info [ddrcode/rules.mk] including key_overrides.c)
    src += features/key_overrides.c
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    $(info [ddrcode/rules.mk] including rgb_matrix.c)
    src += features/rgb_matrix.c
endif

$(info [ddrcode/rules.mk] end)
