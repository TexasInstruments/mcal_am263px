MODULE_NAME = spi

include srcs.mk
include $(mcal_PATH)/include/hw/inc.mk
include $(mcal_PATH)/Dma/inc.mk

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig

PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS)

# Include common make files
include $(MAKERULEDIR)/common.mk
