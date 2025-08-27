WDG_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Wdg_Demo_Cfg

SRCDIR += $(WDG_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(WDG_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Wdg_Cfg.c Wdg_Lcfg.c Wdg_PBcfg.c
