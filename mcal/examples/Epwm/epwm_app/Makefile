APP_NAME = epwm_app

# Get the list of src dir, include dir and source files to compile using module mk files
include $(mcal_PATH)/include/hw/inc.mk
include $(mcal_PATH)/include/memmap/inc.mk
include $(mcal_PATH)/Adc/srcs.mk
include $(mcal_PATH)/Dma/srcs.mk
include $(mcal_PATH)/Epwm/srcs.mk
include $(mcal_PATH)/I2c/srcs.mk
include $(mcal_PATH)/Mcu/srcs.mk
include $(mcal_PATH)/Port/srcs.mk
include $(mcal_PATH)/examples/Utils/srcs.mk
include $(mcal_PATH)/examples/Utils/srcs_autosar_stub.mk
include $(mcal_PATH)/examples/Utils/srcs_startup.mk
include $(mcal_PATH)/examples_config/Adc_Demo_Cfg/srcs.mk
include $(mcal_PATH)/examples_config/Cdd_I2c_Demo_Cfg/srcs.mk
include $(mcal_PATH)/examples_config/Dma_Demo_Cfg/srcs.mk
include $(mcal_PATH)/examples_config/Epwm_Demo_Cfg/srcs.mk
include $(mcal_PATH)/examples_config/Mcu_Demo_Cfg/srcs.mk
include $(mcal_PATH)/examples_config/Port_Demo_Cfg/srcs.mk
include ../soc/srcs.mk
ifeq ($(SOC), am263px)
  include $(mcal_PATH)/examples/Utils/srcs_pmic.mk
endif

SRCDIR += .
INCDIR += .
SRCS_COMMON += Cdd_Pwm_App.c

CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS)
LNKCMD_FILE = $(mcal_PATH)/examples/lnk_r5_$(SOC)_$(COMPILER).cmd

# Include common make files
include $(MAKERULEDIR)/common.mk
