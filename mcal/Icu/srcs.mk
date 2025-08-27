ICU_PATH=$(mcal_PATH)/Icu

SRCDIR += $(ICU_PATH)/src
INCDIR += $(ICU_PATH)/include
SRCS_COMMON += Icu.c Icu_Priv.c Icu_Irq.c ecap.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(ICU_PATH)/V0
  INCDIR += $(ICU_PATH)/V0
endif
