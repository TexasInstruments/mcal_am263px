include $(mcal_PATH)/Dma/inc.mk

SRCDIR += $(mcal_PATH)/Dma/src
SRCS_COMMON += Cdd_Dma.c Cdd_Dma_Irq.c Cdd_Dma_Priv.c Cdd_Dma_soc.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Dma/V0
