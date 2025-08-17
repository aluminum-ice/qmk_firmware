ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
SRC += features/casemodes.c

COMBO_ENABLE = yes
UNICODE_ENABLE = yes