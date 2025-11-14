include $(mcal_PATH)/Adc/inc.mk

SRCDIR += $(mcal_PATH)/Adc/src
SRCS_COMMON += Adc.c Adc_Priv.c Adc_Utils.c Adc_Platform.c Adc_Irq.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Adc/V0
