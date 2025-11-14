include $(mcal_PATH)/Mcu/inc.mk

SRCDIR += $(mcal_PATH)/Mcu/src $(mcal_PATH)/include/hw/$(PLATFORM)
SRCS_COMMON += Mcu.c Mcu_Priv.c Mcal_Libs_Utils.c
# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263))
  SRCDIR += $(mcal_PATH)/Mcu/V0
endif
ifeq ($(SOC), $(filter $(SOC), am263px))
  SRCDIR += $(mcal_PATH)/Mcu/V2
endif
ifeq ($(SOC), $(filter $(SOC), am261))
  SRCDIR += $(mcal_PATH)/Mcu/V3
endif
