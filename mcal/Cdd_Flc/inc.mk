ifeq ($(SOC), $(filter $(SOC), am263px am261))
  INCDIR += $(mcal_PATH)/Cdd_Flc/include $(mcal_PATH)/Cdd_Flc/src/$(PLATFORM)
endif
