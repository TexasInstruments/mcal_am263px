include $(mcal_PATH)/Pwm/inc.mk

SRCDIR += $(mcal_PATH)/Pwm/src
SRCS_COMMON += Pwm.c Pwm_Priv.c Pwm_Irq.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Pwm/V0
SRCS_COMMON += Pwm_Sfo.c
