DMA_PATH=$(mcal_PATH)/Dma

SRCDIR += $(DMA_PATH)/src
INCDIR += $(DMA_PATH)/include
SRCS_COMMON += Cdd_Dma.c Cdd_Dma_Irq.c Cdd_Dma_Priv.c Cdd_Dma_soc.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(DMA_PATH)/V0
  INCDIR += $(DMA_PATH)/V0
endif
