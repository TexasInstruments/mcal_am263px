# Filename: Makefile
#
# This file is the makefile for building PORT example app.
#
#   Copyright (c) 2022-2023 Texas Instruments Incorporated
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

APP_NAME = port_app

ifeq ($(SOC), am263)
APP_SOC_FILES = V0
endif

ifeq ($(SOC), am261)
APP_SOC_FILES = V0
endif

ifeq ($(SOC), am273)
APP_SOC_FILES = V1
endif

ifeq ($(SOC), am2732s)
APP_SOC_FILES = V1
endif


SRCDIR = . ../Utils ../Utils/$(COMPILER) ../Utils/$(COMPILER)/$(SOC) ../Utils/$(SOC)
SRCDIR += $(autosarConfigSrc_PATH)/Dio_Demo_Cfg/soc/$(SOC)/$(CORE)/src 
SRCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += soc/$(SOC)/$(CORE)
INCDIR = .
INCDIR +=../Utils/$(SOC)
INCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/include
INCDIR += $(mcal_PATH)/Port/$(APP_SOC_FILES)
INCDIR += soc/$(SOC)/$(CORE)
INCDIR += $(autosarConfigSrc_PATH)/../examples/Port 
INCDIR += $(mcal_PATH)/include/hw/$(PLATFORM) 
INCDIR += $(mcal_PATH)/include/hw
#INCDIR += $(mcal_PATH)/Mcu/$(APP_SOC_FILES)

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig dio mcu port app_utils

INCLUDE_INTERNAL_INTERFACES = portAppPriv
portAppPriv_INCLUDE =  $(mcal_PATH)/include $(mcal_PATH)/include/hw/$(SOCFAMILY)

# List all the components required by the application
COMP_LIST_COMMON  =  dio mcu port app_utils

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = PortApp.c PortApp_Startup.c
SRCS_COMMON +=Dio_Cfg.c Dio_Lcfg.c  
SRCS_COMMON += Dem.c
SRCS_COMMON += Det.c

ifeq ($(PLATFORM), am273)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am273x_Intr.c Port_Cfg.c 
endif

ifeq ($(PLATFORM), am2732s)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am2732s_Intr.c Port_Cfg.c 
endif

ifeq ($(SOC), am263)
SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_PBcfg_Intr.c Port_Cfg.c
endif

ifeq ($(SOC), am261)
  SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_Cfg.c Port_PBcfg.c
endif

ifeq ($(SOC), am263px)
  SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_Cfg.c 
  ifeq ($(PACKAGE), SIP)
    SRCS_COMMON += Port_PBcfg_SIP.c
  else
    ifeq ($(PACKAGE), C)
      SRCS_COMMON += Port_PBcfg_C.c
    else
      SRCS_COMMON += Port_PBcfg_Intr.c
    endif
  endif
endif

SRCS_ASM_COMMON += sys_startup.asm sys_intvecs.asm

CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS) -D$(SOCFAMILY)

LNKCMD_FILE = ../lnk_r5_$(SOCFAMILY)_$(COMPILER).cmd


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
