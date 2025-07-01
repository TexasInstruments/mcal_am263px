APP_NAME = cdd_flc_app

# Get the list of src dir, include dir and source files to compile using module mk files
include $(mcal_PATH)/include/hw/inc.mk
include $(mcal_PATH)/include/memmap/inc.mk
include $(mcal_PATH)/Cdd_Flc/srcs.mk
include $(mcal_PATH)/Mcu/srcs.mk
include $(mcal_PATH)/Port/srcs.mk
include $(mcal_PATH)/examples/Utils/srcs_autosar_stub.mk
include $(mcal_PATH)/examples/Utils/srcs_startup.mk
include $(mcal_PATH)/examples_config/Cdd_Flc_Demo_Cfg/srcs.mk
include $(mcal_PATH)/examples_config/Mcu_Demo_Cfg/srcs.mk
include $(mcal_PATH)/examples_config/Port_Demo_Cfg/srcs.mk
include soc/srcs.mk

# List all the components/interfaces/libraries required by the application
INCLUDE_EXTERNAL_INTERFACES = app_utils
COMP_LIST_COMMON = app_utils

SRCDIR += .
INCDIR += .
SRCS_COMMON += CddFlcApp.c

CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS)
LNKCMD_FILE = $(mcal_PATH)/examples/lnk_r5_$(SOC)_$(COMPILER).cmd

# Include common make files
include $(MAKERULEDIR)/common.mk
