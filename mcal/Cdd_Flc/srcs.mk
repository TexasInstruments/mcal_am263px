include $(mcal_PATH)/Cdd_Flc/inc.mk

ifeq ($(SOC), $(filter $(SOC), am263px am261))
  SRCDIR += $(mcal_PATH)/Cdd_Flc/src
  SRCS_COMMON += Cdd_Flc.c
endif
