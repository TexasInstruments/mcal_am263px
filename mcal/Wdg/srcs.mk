include $(mcal_PATH)/Wdg/inc.mk

SRCDIR += $(mcal_PATH)/Wdg/src
SRCS_COMMON += Wdg.c Wdg_Priv.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Wdg/V0
