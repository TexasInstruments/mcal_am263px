SPI_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Spi_Demo_Cfg

SRCDIR += $(SPI_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(SPI_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Spi_Cfg.c Spi_Lcfg.c Spi_PBCfg.c
