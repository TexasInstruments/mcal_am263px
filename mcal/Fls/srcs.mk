include $(mcal_PATH)/Fls/inc.mk

SRCDIR += $(mcal_PATH)/Fls/src
SRCS_COMMON += Fls.c Fls_Irq.c
# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263))
  SRCDIR += $(mcal_PATH)/Fls/V0
  SRCS_COMMON += Fls_Brd_Nor_Qspi.c Fls_Qspi.c Fls_Qspi_Edma.c
endif
ifeq ($(SOC), $(filter $(SOC), am263px am261))
  SRCDIR += $(mcal_PATH)/Fls/V2
  SRCS_COMMON += Fls_Brd_Nor_Ospi.c Fls_Ospi.c Fls_Ospi_Edma.c
endif
