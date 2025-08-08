DMA_PATH=$(mcal_PATH)/Dma

INCDIR += $(DMA_PATH)/include

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  INCDIR += $(DMA_PATH)/V0
endif
