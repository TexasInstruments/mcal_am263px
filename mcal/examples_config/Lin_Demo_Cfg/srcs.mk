LIN_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Lin_Demo_Cfg

SRCDIR += $(LIN_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(LIN_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Lin_Cfg.c Lin_PBcfg.c
