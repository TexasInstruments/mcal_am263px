include $(mcal_PATH)/I2c/inc.mk

SRCDIR += $(mcal_PATH)/I2c/src
SRCS_COMMON += Cdd_I2c.c Cdd_I2c_Irq.c Cdd_I2c_Priv.c Cdd_I2c_Utils.c
# SOC specific files
SRCDIR += $(mcal_PATH)/I2c/V0
SRCS_COMMON += Cdd_I2c_Hw.c
