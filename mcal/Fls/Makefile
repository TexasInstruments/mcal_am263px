MODULE_NAME = fls

ifeq ($(SOC), $(filter $(SOC), am263))
SOC_FILES = V0
endif
ifeq ($(SOC), $(filter $(SOC), am273))
SOC_FILES = V1
endif
ifeq ($(SOC), $(filter $(SOC), am263px am261))
SOC_FILES = V2
endif

SRCDIR = src $(SOC_FILES)
INCDIR = src
INCDIR += $(mcal_PATH)/Dma/include
INCDIR += $(mcal_PATH)/Dma/$(SOC)
INCDIR += $(mcal_PATH)/examples/Utils/CLANG/am263px
# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = fls
INCLUDE_INTERNAL_INTERFACES += flsPriv

MODULE_SRC_BASE_PATH := $(mcal_PATH)/Fls

flsPriv_INCLUDE =  $(MODULE_SRC_BASE_PATH) src/hw src/hw/$(SOCFAMILY) \
                   $(mcal_PATH)/include $(mcal_PATH)/include/hw/$(PLATFORM) \
                   $(mcal_PATH)/include/hw \
                   include src/hw include src $(SOC_FILES)
flsPriv_INCLUDE += $(mcal_PATH)/Fls/$(SOC_FILES)

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += Fls.c

ifeq ($(SOC), $(filter $(SOC), am263px am261))
SRCS_$(SOCFAMILY) += Fls_Brd_Nor_Ospi.c
SRCS_$(SOCFAMILY) += Fls_Irq.c
SRCS_$(SOCFAMILY) += Fls_Nor_config.c
SRCS_$(SOCFAMILY) += Fls_Ospi.c
SRCS_$(SOCFAMILY) += Fls_Ospi_Edma.c
endif
ifeq ($(SOC), am263)
SRCS_$(SOCFAMILY) += Fls_Brd_Nor_Qspi.c
SRCS_$(SOCFAMILY) += Fls_Irq.c
SRCS_$(SOCFAMILY) += Fls_Nor_config.c
SRCS_$(SOCFAMILY) += Fls_Qspi.c
SRCS_$(SOCFAMILY) += Fls_Qspi_Edma.c
endif
ifeq ($(SOC), am273)
SRCS_$(SOCFAMILY) += Fls_Brd_Nor_Qspi.c
SRCS_$(SOCFAMILY) += Fls_Irq.c
SRCS_$(SOCFAMILY) += Fls_Nor_config.c
SRCS_$(SOCFAMILY) += Fls_Qspi.c
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
