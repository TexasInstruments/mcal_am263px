SPI_PATH=$(mcal_PATH)/Spi

SRCDIR += $(SPI_PATH)/src
INCDIR += $(SPI_PATH)/include
SRCS_COMMON += Spi.c Spi_Priv.c Spi_Utils.c Spi_Irq.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(SPI_PATH)/V0
  INCDIR += $(SPI_PATH)/V0
  SRCS_COMMON += Spi_Mcspi.c Spi_Dma.c
endif
