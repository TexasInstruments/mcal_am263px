ETH_DEMO_PBCFG_PATH=$(mcal_PATH)/examples_config/Eth_Demo_PBcfg

SRCDIR += $(ETH_DEMO_PBCFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(ETH_DEMO_PBCFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Eth_Cfg.c Eth_Lcfg.c Eth_PBcfg.c
