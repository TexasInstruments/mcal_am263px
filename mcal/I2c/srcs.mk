I2C_PATH=$(mcal_PATH)/I2c

SRCDIR += $(I2C_PATH)/src
INCDIR += $(I2C_PATH)/include
SRCS_COMMON += Cdd_I2c.c Cdd_I2c_Irq.c Cdd_I2c_priv.c

# SOC specific files
SRCDIR += $(I2C_PATH)/V0
INCDIR += $(I2C_PATH)/V0
