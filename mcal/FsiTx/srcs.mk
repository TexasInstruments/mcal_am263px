FSITX_PATH=$(mcal_PATH)/FsiTx

SRCDIR += $(FSITX_PATH)/src
INCDIR += $(FSITX_PATH)/include $(SRCDIR)
SRCS_COMMON += Cdd_FsiTx.c Cdd_FsiTx_Irq.c Cdd_FsiTx_Priv.c Cdd_FsiTx_Platform.c

# SOC specific files
SRCDIR += $(FSITX_PATH)/V0
