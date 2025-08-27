MODULE_NAME = i2c

include srcs.mk
include $(mcal_PATH)/include/hw/inc.mk

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig

PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS)

# Include common make files
include $(MAKERULEDIR)/common.mk
