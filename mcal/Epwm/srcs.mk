EPWM_PATH=$(mcal_PATH)/Epwm

SRCDIR += $(EPWM_PATH)/src
INCDIR += $(EPWM_PATH)/include
SRCS_COMMON += Cdd_Pwm.c Cdd_Pwm_Irq.c Cdd_Pwm_Priv.c Cdd_Pwm_Sfo.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(EPWM_PATH)/V0
  INCDIR += $(EPWM_PATH)/V0
endif
