MODULE_NAME = ipc

ifeq ($(SOC),$(filter $(SOC),am263 am263px))
SOC_FILES = V0
endif
ifeq ($(SOC), am273)
SOC_FILES = V1
endif
ifeq ($(SOC), am261)
SOC_FILES = V2
endif

SRCDIR = src $(SOC_FILES)
INCDIR = include $(SOC_FILES) \
         $(mcal_PATH)/include \
         $(mcal_PATH)/include/hw/$(PLATFORM) \
         $(mcal_PATH)/include/hw include

# List all the external components/interfaces, whose interface header files
# need to be included for this component

# External dependencies
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig

# Add MCU PLUS SDK in external dependencies
EXT_CFLAGS = -DSOC_AM263X

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = ipc

MODULE_SRC_BASE_PATH := $(mcal_PATH)/$(mcal_RELPATH)

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += Cdd_Ipc.c Cdd_Ipc_Irq.c ipc_notify_v1_cfg_lld.c ipc_notify_v1_lld.c ipc_rpmsg_lld_vring.c ipc_rpmsg_lld.c ipc_notify_lld_utils.c
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
