FSIRX_PATH=$(mcal_PATH)/FsiRx

SRCDIR += $(FSIRX_PATH)/src
INCDIR += $(FSIRX_PATH)/include $(SRCDIR)
SRCS_COMMON += Cdd_FsiRx.c Cdd_FsiRx_Priv.c Cdd_FsiRx_Platform.c Cdd_FsiRx_Irq.c

# SOC specific files
SRCDIR += $(FSIRX_PATH)/V0
