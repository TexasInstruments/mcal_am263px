ADC_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Adc_Demo_Cfg

SRCDIR += $(ADC_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(ADC_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Adc_Cfg.c Adc_PBcfg.c
