include $(mcal_PATH)/Icu/inc.mk

SRCDIR += $(mcal_PATH)/Icu/src
SRCS_COMMON += Icu.c Icu_Priv.c Icu_Irq.c ecap.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Icu/V0
