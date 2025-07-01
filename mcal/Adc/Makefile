MODULE_NAME = adc

ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
SOC_FILES = V0
endif
ifeq ($(SOC), am273)
SOC_FILES = V1
endif

SRCDIR = src $(SOC_FILES) 
INCDIR = src \
         $(mcal_PATH)/include \
         $(mcal_PATH)/include/hw/$(PLATFORM) \
         $(mcal_PATH)/include/hw \
         include $(SRCDIR)
         
# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig dma

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = adc

MODULE_SRC_BASE_PATH := $(mcal_PATH)/Adc

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += Adc.c 
SRCS_$(SOCFAMILY) += Adc_Priv.c Adc_Utils.c Adc_Platform.c Adc_Irq.c
ifeq ($(SOC), am273)
SRCS_$(SOCFAMILY) += Adc_Temp.c
endif
PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS)

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

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
