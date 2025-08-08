UTILS_PATH=$(mcal_PATH)/examples/Utils
include $(mcal_PATH)/examples_config/Cdd_I2c_Demo_Cfg/srcs.mk

ifeq ($(SOC), $(filter $(SOC), am263px))
  SRCDIR += $(UTILS_PATH)
  INCDIR += $(UTILS_PATH)
  SRCS_COMMON += app_utilsI2c.c
endif
