UTILS_PATH=$(mcal_PATH)/examples/Utils

ifeq ($(SOC), $(filter $(SOC), am263px))
  SRCDIR += $(UTILS_PATH)/$(SOC)/IoMux
  INCDIR += $(UTILS_PATH)/$(SOC)/IoMux
  SRCS_COMMON += ioexp_tca6416_6424.c
endif
