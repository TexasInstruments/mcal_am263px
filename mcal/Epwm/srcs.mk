include $(mcal_PATH)/Epwm/inc.mk

SRCDIR += $(mcal_PATH)/Epwm/src
SRCS_COMMON += Cdd_Pwm.c Cdd_Pwm_Irq.c Cdd_Pwm_Priv.c Cdd_Pwm_Sfo.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Epwm/V0
