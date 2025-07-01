FLS_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Fls_Demo_Cfg

SRCDIR += $(FLS_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(FLS_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Fls_Cfg.c Fls_PBcfg.c
