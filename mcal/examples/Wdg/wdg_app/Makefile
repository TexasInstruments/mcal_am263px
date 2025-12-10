APP_NAME = wdg_app

# Get the list of src dir, include dir and source files to compile using module mk files
include $(mcal_PATH)/include/hw/inc.mk
include $(mcal_PATH)/include/memmap/inc.mk
include $(mcal_PATH)/Gpt/srcs.mk
include $(mcal_PATH)/Mcu/srcs.mk
include $(mcal_PATH)/Port/srcs.mk
include $(mcal_PATH)/Wdg/srcs.mk
include $(mcal_PATH)/examples/Utils/srcs.mk
include $(mcal_PATH)/examples/Utils/srcs_autosar_stub.mk
include $(mcal_PATH)/examples/Utils/srcs_startup.mk
include $(mcal_PATH)/examples_config/Gpt_Demo_Cfg/srcs.mk
ifeq ($(PLATFORM), $(filter $(PLATFORM), am263px am261))
   include $(mcal_PATH)/Fls/srcs.mk
   include $(mcal_PATH)/examples_config/Fls_OSPI_SBL_Support_Cfg/srcs.mk
   include $(mcal_PATH)/Dma/srcs.mk
endif
include $(mcal_PATH)/examples_config/Mcu_Demo_Cfg/srcs.mk
include $(mcal_PATH)/examples_config/Port_Demo_Cfg/srcs.mk
include $(mcal_PATH)/examples_config/Wdg_Demo_Cfg/srcs.mk
include soc/srcs.mk

SRCDIR += .
INCDIR += .
SRCS_COMMON += WdgApp.c

CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS)
LNKCMD_FILE = $(mcal_PATH)/examples/lnk_r5_$(SOC)_$(COMPILER).cmd

# Include common make files
include $(MAKERULEDIR)/common.mk
