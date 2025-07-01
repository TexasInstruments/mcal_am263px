ICU_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Icu_Demo_Cfg

SRCDIR += $(ICU_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(ICU_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Icu_Cfg.c Icu_PBcfg.c
