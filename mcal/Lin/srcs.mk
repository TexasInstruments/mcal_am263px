include $(mcal_PATH)/Lin/inc.mk

SRCDIR += $(mcal_PATH)/Lin/src
SRCS_COMMON += Lin.c Lin_Priv.c Lin_Irq.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Lin/V0
