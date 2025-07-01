MODULE_NAME = uart

ifeq ($(SOC),$(filter $(SOC),am263 am263px am261))
SOC_FILES = V0
endif
ifeq ($(SOC), am273)
SOC_FILES = V1
endif

SRCDIR = src $(SOC_FILES)
INCDIR = include $(mcal_PATH)/include/hw/$(PLATFORM) \
         $(mcal_PATH)/include/hw $(SOC_FILES)

# List all the external components/interfaces, whose interface header files
# need to be included for this component

# External dependencies
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig

# List all the internal submodules whose interface header files
# need to be included for this module
ifeq ($(SOC),$(filter $(SOC),am263 am263px am273 am2732s))
INCLUDE_INTERNAL_INTERFACES = dma
endif

MODULE_SRC_BASE_PATH := $(mcal_PATH)\$(mcal_RELPATH)

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = Cdd_Uart.c Cdd_Uart_Irq.c
SRCS_COMMON += Cdd_Uart_Priv.c uart.c uart_dma_edma.c
PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS)

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)\build\makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
