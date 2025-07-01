# Filename: Makefile
#
# This file is the makefile for building CAN example app.
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

APP_NAME = ipc_safeipc_app
 
SRCDIR = . ../../Utils ../../Utils/$(COMPILER) ../../Utils/$(COMPILER)/$(SOC) ../../Utils/$(SOC) 
SRCDIR += $(mcal_PATH)/examples/Ipc/Ipc_app_safeipc

SRCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/SafeIpc_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += $(mcal_PATH)/examples/Ipc/soc/$(SOC)/$(CORE)

INCDIR = . $(mcal_PATH)/examples/Config\
		   $(mcal_PATH)/include \
		   $(mcal_PATH)/include/hw \
		   $(mcal_PATH)/include/hw/$(PLATFORM) \
		   ../../Utils/$(SOC) \
		   $(mcal_PATH)/Ipc/$(SOC_FILES) \
		   $(mcal_PATH)/examples/Ipc/soc/$(SOC)/$(CORE)

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig ipc mcu port app_utils

# List all the components required by the application
COMP_LIST_COMMON  =  ipc mcu port app_utils

EXT_CFLAGS = -DSOC_AM263X

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = Cdd_Ipc_App_Startup.c Cdd_Ipc_safeipc_app.c Cdd_Ipc_PBCfg.c Os.c

ifeq ($(SOC), am273)

ifeq ($(PLATFORM), am2732s)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am2732s.c Port_Cfg.c
endif

ifeq ($(PLATFORM), am273)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am273x.c Port_Cfg.c
endif

endif

ifeq ($(SOC), am263)
SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_PBcfg.c Port_Cfg.c
endif

ifeq ($(SOC), am263px)
  SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_Cfg.c
  ifeq ($(PACKAGE), SIP)
    SRCS_COMMON += Port_PBcfg_SIP.c
  else
    ifeq ($(PACKAGE), C)
      SRCS_COMMON += Port_PBcfg_C.c
    else
      SRCS_COMMON += Port_PBcfg.c
    endif
  endif
endif

SRCS_ASM_COMMON += sys_intvecs.asm sys_startup.asm
SRCS_COMMON += Dem.c Det.c
CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS) -D$(SOCFAMILY)

LNKCMD_FILE = lnk_r5_SafeIpc_$(SOCFAMILY)_$(COMPILER).cmd


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
