CDD_FLC_PATH=$(mcal_PATH)/Cdd_Flc

SRCDIR += $(CDD_FLC_PATH)/src
INCDIR += $(CDD_FLC_PATH)/include $(CDD_FLC_PATH)/src/$(PLATFORM)
SRCS_COMMON += Cdd_Flc.c
