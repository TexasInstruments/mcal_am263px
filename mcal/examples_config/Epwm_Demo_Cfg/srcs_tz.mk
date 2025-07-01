EPWM_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Epwm_Demo_Cfg

SRCDIR += $(EPWM_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(EPWM_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Cdd_Pwm_Cfg_Tz.c Cdd_Pwm_PBcfg_Tz.c
