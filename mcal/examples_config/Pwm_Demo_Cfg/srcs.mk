PWM_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Pwm_Demo_Cfg

SRCDIR += $(PWM_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(PWM_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Pwm_Cfg.c Pwm_PBcfg.c
