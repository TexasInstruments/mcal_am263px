APP_NAME = eth_load_app

SRCDIR = soc/$(SOC)/$(CORE)

ifeq ($(BUILD_VARIANT), linktime)
SRCDIR += $(autosarConfigSrc_PATH)/Eth_Demo_Lcfg/soc/$(SOC)/$(CORE)/src
else
ifeq ($(BUILD_VARIANT), postbuild)
SRCDIR += $(autosarConfigSrc_PATH)/Eth_Demo_PBcfg/soc/$(SOC)/$(CORE)/src
else
SRCDIR += $(autosarConfigSrc_PATH)/Eth_Demo_Cfg/soc/$(SOC)/$(CORE)/src
endif
endif

SRCDIR += $(autosarConfigSrc_PATH)/EthTrcv_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/src
INCDIR = .
INCDIR += soc/$(SOC)/$(CORE)

ifeq ($(BUILD_VARIANT), linktime)
INCDIR += $(autosarConfigSrc_PATH)/Eth_Demo_Lcfg/soc/$(SOC)/$(CORE)/include
else
ifeq ($(BUILD_VARIANT), postbuild)
INCDIR += $(autosarConfigSrc_PATH)/Eth_Demo_PBcfg/soc/$(SOC)/$(CORE)/include
else
INCDIR += $(autosarConfigSrc_PATH)/Eth_Demo_Cfg/soc/$(SOC)/$(CORE)/include
endif
endif

INCDIR += $(mcal_PATH)/include/hw/$(PLATFORM)
INCDIR += $(mcal_PATH)/include/hw

INCDIR += $(mcal_PATH)/examples/Eth/utils
INCDIR += $(mcal_PATH)/examples/Eth/utils/soc
INCDIR += $(mcal_PATH)/examples/Eth/utils/soc/$(SOC)/$(CORE)
SRCDIR += $(mcal_PATH)/examples/Eth/utils
SRCDIR += $(mcal_PATH)/examples/Eth/utils/soc/$(SOC)
SRCDIR += $(mcal_PATH)/examples/Eth/utils/soc/$(SOC)/$(CORE)

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig eth ethtrcv mcu port app_utils

INCLUDE_INTERNAL_INTERFACES = ethAppPriv
ethAppPriv_INCLUDE = $(mcal_PATH)/include $(mcal_PATH)/include/hw/$(SOCFAMILY) $(mcal_PATH)/include/hw

# List all the components required by the application
COMP_LIST_COMMON = eth ethtrcv

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = EthLoadApp.c Eth_Cfg.c Eth_Lcfg.c Eth_PBcfg.c EthTrcv_Lcfg.c
SRCS_COMMON += app_utils.c EthLoadUtils.c

SRCDIR += $(mcal_PATH)/examples/Utils
SRCS_COMMON += Dem.c Det.c

# MCAL utils
SRCS_COMMON += McalUtils.c

ifeq ($(SOC), am273)
  SRCS_COMMON += EthApp_Startup.c EthTrcv_cfg.c EthTrcv_PBcfg.c Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_Cfg.c
  ifeq ($(PLATFORM), am2732s)
    SRCS_COMMON += Port_PBcfg_am2732s.c
  endif
  ifeq ($(PLATFORM), am273)
    SRCS_COMMON += Port_PBcfg_am273x.c
  endif
endif

ifeq ($(SOC), am263)
  SRCS_COMMON += EthApp_Startup.c EthTrcv_Cfg.c EthTrcv_PBcfg.c Mcu_PBcfg.c Mcu_Cfg.c Port_PBcfg.c Port_Cfg.c
endif

ifeq ($(SOC), am261)
  SRCS_COMMON += EthApp_Startup.c EthTrcv_Cfg.c EthTrcv_PBcfg.c Mcu_PBcfg.c Mcu_Cfg.c Port_PBcfg_Eth.c Port_Cfg.c
endif

ifeq ($(SOC), am263px)
  SRCS_COMMON += EthApp_Startup.c EthTrcv_Cfg.c Mcu_PBcfg.c Mcu_Cfg.c Port_Cfg.c
  ifeq ($(PACKAGE), SIP)
    SRCS_COMMON += EthTrcv_PBcfg.c Port_PBcfg_SIP.c
  else
    ifeq ($(PACKAGE), C)
      SRCS_COMMON += EthTrcv_PBcfg_C.c Port_PBcfg_C.c
    else
      SRCS_COMMON += EthTrcv_PBcfg.c Port_PBcfg.c
    endif
  endif
endif

#SRCS_ASM_COMMON += sys_intvecs.asm sys_startup.asm

# Common source files and CFLAGS across all platforms and cores
CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS) -D$(SOCFAMILY) -DSOC_$(SOCFAMILY)

# Linker file
LNKCMD_FILE = soc/$(SOC)/$(CORE)/eth_load_app_linker.cmd

# Add MCU+SDK external dependencies
EXT_INCS = -I$(MCUPLUSSDK_ROOTDIR)/source -I$(MCUPLUSSDK_ROOTDIR)/source -I$(MCUPLUSSDK_ROOTDIR)/source/kernel/freertos/FreeRTOS-Kernel/include \
           -I$(MCUPLUSSDK_ROOTDIR)/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F

ifeq ($(SOC), am263)
EXT_CFLAGS = -DSOC_AM263X
EXT_INCS += -I$(MCUPLUSSDK_ROOTDIR)/source/kernel/freertos/config/am263x/r5f
ifneq ($(wildcard $(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am263x.r5f.ti-arm-clang.$(PROFILE).lib),)
EXT_LIBS = -l$(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am263x.r5f.ti-arm-clang.$(PROFILE).lib
else
EXT_LIBS = -l$(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am263x.r5f.ti-arm-clang.freertos.$(PROFILE).lib
endif
EXT_LIBS += -l$(MCUPLUSSDK_ROOTDIR)/source/kernel/freertos/lib/freertos.am263x.r5f.ti-arm-clang.$(PROFILE).lib
endif

ifeq ($(SOC), am261)
EXT_CFLAGS = -DSOC_AM261X
EXT_INCS += -I$(MCUPLUSSDK_ROOTDIR)/source/kernel/freertos/config/am261x/r5f
ifneq ($(wildcard $(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am261x.r5f.ti-arm-clang.$(PROFILE).lib),)
EXT_LIBS = -l$(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am261x.r5f.ti-arm-clang.$(PROFILE).lib
else
EXT_LIBS = -l$(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am261x.r5f.ti-arm-clang.freertos.$(PROFILE).lib
endif
EXT_LIBS += -l$(MCUPLUSSDK_ROOTDIR)/source/kernel/freertos/lib/freertos.am261x.r5f.ti-arm-clang.$(PROFILE).lib
endif

ifeq ($(SOC), am263px)
EXT_CFLAGS = -DSOC_AM263PX
EXT_INCS += -I$(MCUPLUSSDK_ROOTDIR)/source/kernel/freertos/config/am263px/r5f
ifneq ($(wildcard $(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am263px.r5f.ti-arm-clang.$(PROFILE).lib),)
EXT_LIBS = -l$(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am263px.r5f.ti-arm-clang.$(PROFILE).lib
else
EXT_LIBS = -l$(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am263px.r5f.ti-arm-clang.freertos.$(PROFILE).lib
endif
EXT_LIBS +=  -l$(MCUPLUSSDK_ROOTDIR)/source/kernel/freertos/lib/freertos.am263px.r5f.ti-arm-clang.$(PROFILE).lib
endif

ifeq ($(SOC), am273)
EXT_CFLAGS = -DSOC_AM273X
EXT_INCS += -I$(MCUPLUSSDK_ROOTDIR)/source/kernel/freertos/config/am273x/r5f
ifneq ($(wildcard $(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am273x.r5f.ti-arm-clang.$(PROFILE).lib),)
EXT_LIBS = -l$(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am273x.r5f.ti-arm-clang.$(PROFILE).lib
else
EXT_LIBS = -l$(MCUPLUSSDK_ROOTDIR)/source/drivers/lib/drivers.am273x.r5f.ti-arm-clang.freertos.$(PROFILE).lib
endif
EXT_LIBS += -l$(MCUPLUSSDK_ROOTDIR)/source/kernel/freertos/lib/freertos.am273x.r5f.ti-arm-clang.$(PROFILE).lib
endif

# Use FreeRTOS
EXT_CFLAGS += -DOS_FREERTOS

SRCDIR += soc/$(SOC)/syscfg
INCDIR += soc/$(SOC)/syscfg
SRCS_COMMON += ti_board_config.c \
               ti_board_open_close.c \
               ti_dpl_config.c \
               ti_drivers_config.c \
               ti_drivers_open_close.c \
               ti_pinmux_config.c \
               ti_power_clock_config.c

SRCS_COMMON += os_wrapper.c

# Core/SoC/platform specific source files and CFLAGS
# Example:
# SRCS_<core/SoC/platform-name> =
# CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
# and need not be explicitly specified here

# Nothing beyond this point
