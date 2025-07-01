# Filename: Makefile
#
# This file is the makefile for building IPC example app.
#
#   Copyright (c) 2022 Texas Instruments Incorporated
#
#   All rights reserved. Property of Texas Instruments Incorporated.
#   Restricted rights to use, duplicate or disclose this code are
#   granted through contract.
#
#   The program may not be used without the written permission
#   of Texas Instruments Incorporated or against the terms and conditions
#   stipulated in the agreement under which this program has been
#   supplied.
#******************************************************************************
APP_NAME = eth_test_app

SRCDIR = . ../../Utils ../../Utils/$(COMPILER) ../../Utils/$(COMPILER)/$(SOC) ../../Utils/$(SOC)
SRCDIR += soc/$(SOC)/$(CORE)

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
INCDIR += . ../../Utils 
INCDIR +=../../Utils/$(COMPILER)
INCDIR += ../../Utils/$(SOC)
INCDIR +=../../Utils/$(COMPILER)/$(SOC)

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
COMP_LIST_COMMON = app_utils eth ethtrcv mcu port 

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = EthTestApp.c app_utilsEth.c Eth_Cfg.c Eth_Lcfg.c Eth_PBcfg.c EthTrcv_Lcfg.c

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
  SRCS_COMMON += EthTrcv_Cfg.c Mcu_PBcfg.c Mcu_Cfg.c Port_Cfg.c
  ifeq ($(PACKAGE), SIP)
    SRCS_COMMON += EthApp_Startup.c EthTrcv_PBcfg.c Port_PBcfg_SIP.c
  else
    ifeq ($(PACKAGE), C)
      SRCS_COMMON += EthApp_Startup_C.c EthTrcv_PBcfg_C.c Port_PBcfg_C.c
    else
      SRCS_COMMON += EthApp_Startup.c EthTrcv_PBcfg.c Port_PBcfg.c
    endif
  endif
endif

SRCS_ASM_COMMON += sys_intvecs.asm sys_startup.asm
SRCS_COMMON += Dem.c

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += EthUtils_Target.c EthUtils.c

CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS) -D$(SOCFAMILY) -DSOC_$(SOCFAMILY)

LNKCMD_FILE = ../../lnk_r5_$(SOCFAMILY)_$(COMPILER).cmd


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
