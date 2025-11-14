include $(mcal_PATH)/Can/inc.mk

SRCDIR += $(mcal_PATH)/Can/src
SRCS_COMMON += Can.c Can_Priv.c Can_Irq.c mcan.c Can_Mcan.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Can/V0
