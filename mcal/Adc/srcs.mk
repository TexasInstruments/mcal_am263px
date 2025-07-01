ADC_PATH=$(mcal_PATH)/Adc

SRCDIR += $(ADC_PATH)/src
INCDIR += $(ADC_PATH)/include $(SRCDIR)
SRCS_COMMON += Adc.c Adc_Priv.c Adc_Utils.c Adc_Platform.c Adc_Irq.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(ADC_PATH)/V0
endif
ifeq ($(SOC), $(filter $(SOC), am273))
  SRCDIR += $(ADC_PATH)/V1
  SRCS_COMMON += Adc_Temp.c
endif
