UTILS_PATH=$(mcal_PATH)/examples/Utils

ifeq ($(SOC), $(filter $(SOC), am263px))
  SRCDIR += $(UTILS_PATH)/$(SOC)/Pmic
  INCDIR += $(UTILS_PATH)/$(SOC)/Pmic
  SRCS_COMMON += AppPimc.c mcspi_v0.c
endif
