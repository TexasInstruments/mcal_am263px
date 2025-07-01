MCU_PATH=$(mcal_PATH)/Mcu

SRCDIR += $(MCU_PATH)/src $(mcal_PATH)/include/hw/$(PLATFORM)
INCDIR += $(MCU_PATH)/include
SRCS_COMMON += Mcu.c Mcu_Priv.c Mcal_Libs_Utils.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263))
  SRCDIR += $(MCU_PATH)/V0
  INCDIR += $(MCU_PATH)/V0
endif
ifeq ($(SOC), $(filter $(SOC), am263px))
  SRCDIR += $(MCU_PATH)/V2
  INCDIR += $(MCU_PATH)/V2
endif
ifeq ($(SOC), $(filter $(SOC), am261))
  SRCDIR += $(MCU_PATH)/V3
  INCDIR += $(MCU_PATH)/V3
endif
ifeq ($(SOC), $(filter $(SOC), am273 am2732s))
  SRCDIR += $(MCU_PATH)/V1
  INCDIR += $(MCU_PATH)/V1
endif
