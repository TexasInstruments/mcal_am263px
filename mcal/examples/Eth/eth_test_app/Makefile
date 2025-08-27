APP_NAME = eth_test_app

# Get the list of src dir, include dir and source files to compile using module mk files
include $(mcal_PATH)/include/hw/inc.mk
include $(mcal_PATH)/include/memmap/inc.mk
include $(mcal_PATH)/Eth/srcs.mk
include $(mcal_PATH)/EthTrcv/srcs.mk
include $(mcal_PATH)/Mcu/srcs.mk
include $(mcal_PATH)/Port/srcs.mk
include $(mcal_PATH)/examples/Utils/srcs.mk
include $(mcal_PATH)/examples/Utils/srcs_autosar_stub.mk
include $(mcal_PATH)/examples/Utils/srcs_eth.mk
include $(mcal_PATH)/examples/Utils/srcs_startup.mk
ifeq ($(BUILD_VARIANT), linktime)
  include $(mcal_PATH)/examples_config/Eth_Demo_Lcfg/srcs.mk
else
  ifeq ($(BUILD_VARIANT), postbuild)
    include $(mcal_PATH)/examples_config/Eth_Demo_PBcfg/srcs.mk
  else
    include $(mcal_PATH)/examples_config/Eth_Demo_Cfg/srcs.mk
  endif
endif
include $(mcal_PATH)/examples_config/EthTrcv_Demo_Cfg/srcs.mk
include $(mcal_PATH)/examples_config/Mcu_Demo_Cfg/srcs.mk
include $(mcal_PATH)/examples_config/Port_Demo_Cfg/srcs_eth.mk
include soc/srcs.mk
include $(mcal_PATH)/examples/Eth/utils/srcs.mk

SRCDIR += .
INCDIR += .
SRCS_COMMON += EthTestApp.c

CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS)
LNKCMD_FILE = $(mcal_PATH)/examples/lnk_r5_$(SOC)_$(COMPILER).cmd

# Include common make files
include $(MAKERULEDIR)/common.mk
