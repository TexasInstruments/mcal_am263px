FLS_OSPI_SBL_SUPPORT_CFG_PATH=$(mcal_PATH)/examples_config/Fls_OSPI_SBL_Support_Cfg

SRCDIR += $(FLS_OSPI_SBL_SUPPORT_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(FLS_OSPI_SBL_SUPPORT_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Cdd_Dma_Cfg.c Fls_Cfg.c Fls_PBcfg.c
