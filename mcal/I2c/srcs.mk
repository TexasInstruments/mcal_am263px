CDD_I2C_PATH=$(mcal_PATH)/I2c

SRCDIR += $(CDD_I2C_PATH)/src
INCDIR += $(CDD_I2C_PATH)/include $(CDD_I2C_PATH)/src
SRCS_COMMON += Cdd_I2c.c Cdd_I2c_Irq.c Cdd_I2c_Priv.c Cdd_I2c_Utils.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(CDD_I2C_PATH)/V0
  INCDIR += $(CDD_I2C_PATH)/V0
  SRCS_COMMON += Cdd_I2c_Hw.c
endif
