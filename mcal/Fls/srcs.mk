FLS_PATH=$(mcal_PATH)/Fls

SRCDIR += $(FLS_PATH)/src
INCDIR += $(FLS_PATH)/include
SRCS_COMMON += Fls.c Fls_Irq.c Fls_Nor_config.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263))
  SRCDIR += $(FLS_PATH)/V0
  INCDIR += $(FLS_PATH)/V0
  # For CacheP APIs
  INCDIR += $(mcal_PATH)/examples/Utils/CLANG/am263
  SRCS_COMMON += Fls_Brd_Nor_Qspi.c Fls_Qspi.c Fls_Qspi_Edma.c
endif
ifeq ($(SOC), $(filter $(SOC), am263px am261))
  SRCDIR += $(FLS_PATH)/V2
  INCDIR += $(FLS_PATH)/V2
  ifeq ($(SOC), $(filter $(SOC), am263px))
    # For CacheP APIs
    INCDIR += $(mcal_PATH)/examples/Utils/CLANG/am263px
  endif
  ifeq ($(SOC), $(filter $(SOC), am261))
    # For CacheP APIs
    INCDIR += $(mcal_PATH)/examples/Utils/CLANG/am261
  endif
  SRCS_COMMON += Fls_Brd_Nor_Ospi.c Fls_Ospi.c Fls_Ospi_Edma.c
endif
ifeq ($(SOC), $(filter $(SOC), am273))
  SRCDIR += $(FLS_PATH)/V1
  INCDIR += $(FLS_PATH)/V1
  # For CacheP APIs
  INCDIR += $(mcal_PATH)/examples/Utils/CLANG/am273
  SRCS_COMMON += Fls_Brd_Nor_Qspi.c Fls_Qspi.c
endif
