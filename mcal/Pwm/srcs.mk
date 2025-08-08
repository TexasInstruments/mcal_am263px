PWM_PATH=$(mcal_PATH)/Pwm

SRCDIR += $(PWM_PATH)/src
INCDIR += $(PWM_PATH)/include
SRCS_COMMON += Pwm.c Pwm_Priv.c Pwm_Irq.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(PWM_PATH)/V0
  INCDIR += $(PWM_PATH)/V0
  SRCS_COMMON += Pwm_Sfo.c
endif
