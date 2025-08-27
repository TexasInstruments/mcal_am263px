FSIRX_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/FsiRx_Demo_Cfg

SRCDIR += $(FSIRX_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(FSIRX_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Cdd_FsiRx_Cfg.c Cdd_FsiRx_PBcfg.c
