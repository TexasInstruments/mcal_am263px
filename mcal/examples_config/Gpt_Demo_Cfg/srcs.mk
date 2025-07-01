GPT_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Gpt_Demo_Cfg

SRCDIR += $(GPT_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(GPT_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Gpt_Cfg.c Gpt_PBcfg.c
