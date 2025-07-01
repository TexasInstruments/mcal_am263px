ETHTRCV_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/EthTrcv_Demo_Cfg

SRCDIR += $(ETHTRCV_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(ETHTRCV_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += EthTrcv_Cfg.c EthTrcv_Lcfg.c EthTrcv_PBcfg.c
