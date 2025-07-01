DIO_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Dio_Demo_Cfg

SRCDIR += $(DIO_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(DIO_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Dio_Cfg.c Dio_Lcfg.c
