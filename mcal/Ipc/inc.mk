include $(mcal_PATH)/Mcal_Lib/inc.mk
INCDIR += $(mcal_PATH)/Ipc/include
# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px))
  INCDIR += $(mcal_PATH)/Ipc/V0
endif
ifeq ($(SOC), $(filter $(SOC), am261))
  INCDIR += $(mcal_PATH)/Ipc/V2
endif
