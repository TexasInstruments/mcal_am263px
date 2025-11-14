include $(mcal_PATH)/FsiRx/inc.mk

SRCDIR += $(mcal_PATH)/FsiRx/src
SRCS_COMMON += Cdd_FsiRx.c Cdd_FsiRx_Priv.c Cdd_FsiRx_Platform.c Cdd_FsiRx_Irq.c
# SOC specific files
SRCDIR += $(mcal_PATH)/FsiRx/V0
