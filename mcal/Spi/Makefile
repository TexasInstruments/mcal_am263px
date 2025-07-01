MODULE_NAME = spi

ifeq ($(SOC),$(filter $(SOC),am263 am263px am261))
SOC_FILES = V0
endif
ifeq ($(SOC), am273)
SOC_FILES = V1
endif

SRCDIR += src $(SOC_FILES)

INCDIR += include src $(SOC_FILES)
INCDIR += $(mcal_PATH)/Dma/include
INCDIR += $(mcal_PATH)/Dma/$(SOC)
INCDIR += $(mcal_PATH)/include/hw/$(PLATFORM)
INCDIR += $(mcal_PATH)/include/hw

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig

# List all the internal submodules whose interface header files
# need to be included for this module
ifeq ($(SOC),$(filter $(SOC),am263 am263px am261))
INCLUDE_INTERNAL_INTERFACES = dma spi
endif
ifeq ($(SOC),$(filter $(SOC),am273 am2732s))
INCLUDE_INTERNAL_INTERFACES = dma spi
endif

MODULE_SRC_BASE_PATH := $(mcal_PATH)/Spi

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += Spi.c Spi_Priv.c Spi_Utils.c Spi_Irq.c  
ifeq ($(SOC),$(filter $(SOC),am263 am263px am261))
SRCS_COMMON += Spi_Mcspi.c Spi_Dma.c
endif
ifeq ($(SOC), am273)
SRCS_COMMON += Spi_Mibspi.c Spi_Qspi.c
endif

PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS)

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
