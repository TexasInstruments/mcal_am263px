include $(mcal_PATH)/Spi/inc.mk

SRCDIR += $(mcal_PATH)/Spi/src
SRCS_COMMON += Spi.c Spi_Priv.c Spi_Utils.c Spi_Irq.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Spi/V0
SRCS_COMMON += Spi_Mcspi.c Spi_Dma.c
