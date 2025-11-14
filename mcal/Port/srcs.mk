include $(mcal_PATH)/Port/inc.mk

SRCDIR += $(mcal_PATH)/Port/src
SRCS_COMMON += Port.c Port_Priv.c Port_Irq.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Port/V0
