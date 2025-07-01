MODULE_NAME = eth

ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
SOC_FILES = V0
endif
ifeq ($(SOC), am273)
SOC_FILES = V1
endif

SRCDIR = src src/cpsw $(SOC_FILES)
INCDIR += $(mcal_PATH)/include
INCDIR += $(mcal_PATH)/include/hw/$(PLATFORM)
INCDIR += $(mcal_PATH)/include/hw
INCDIR += $(mcal_PATH)/Eth/src/cpsw/include
INCDIR += $(mcal_PATH)/Eth/src/hw
INCDIR += $(mcal_PATH)/Eth/$(SOC_FILES)

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig mcu port ethtrcv

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = eth

MODULE_SRC_BASE_PATH := $(mcal_PATH)/Eth

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += Eth.c Eth_Irq.c 
SRCS_$(SOCFAMILY) += Eth_Priv.c Eth_Helpers.c Cpsw.c Cpsw_Ale.c Cpsw_Mdio.c Cpsw_Stats.c Cpsw_Cpts.c Cpsw_Port.c Cpsw_Cpdma.c

PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS)

# Include common make files
ifeq ($(MAKERULEDIR), )
Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
