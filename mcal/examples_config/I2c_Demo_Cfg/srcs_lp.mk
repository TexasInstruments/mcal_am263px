I2C_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/I2c_Demo_Cfg

SRCDIR += $(I2C_DEMO_CFG_PATH)/soc/$(SOC)_lp/r5f0_0/src
INCDIR += $(I2C_DEMO_CFG_PATH)/soc/$(SOC)_lp/r5f0_0/include
SRCS_COMMON += Cdd_I2c_Cfg.c
