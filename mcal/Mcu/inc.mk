INCDIR += $(mcal_PATH)/Mcu/include
# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263))
  INCDIR += $(mcal_PATH)/Mcu/V0
endif
ifeq ($(SOC), $(filter $(SOC), am263px))
  INCDIR += $(mcal_PATH)/Mcu/V2
endif
ifeq ($(SOC), $(filter $(SOC), am261))
  INCDIR += $(mcal_PATH)/Mcu/V3
endif
