FSITX_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/FsiTx_Demo_Cfg

SRCDIR += $(FSITX_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(FSITX_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Cdd_FsiTx_Cfg.c Cdd_FsiTx_PBcfg.c
