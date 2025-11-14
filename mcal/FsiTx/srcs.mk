include $(mcal_PATH)/FsiTx/inc.mk

SRCDIR += $(mcal_PATH)/FsiTx/src
SRCS_COMMON += Cdd_FsiTx.c Cdd_FsiTx_Irq.c Cdd_FsiTx_Priv.c Cdd_FsiTx_Platform.c
# SOC specific files
SRCDIR += $(mcal_PATH)/FsiTx/V0
