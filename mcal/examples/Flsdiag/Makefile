# Filename: Makefile
#
# This file is the makefile for building CAN example app.
#
#   Copyright (c) 2021 Texas Instruments Incorporated
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

APP_NAME = flsdiag_app

ifeq ($(SOC), am263)
APP_SOC_FILES = V0
endif

ifeq ($(SOC), am273)
APP_SOC_FILES = V1
endif

ifeq ($(SOC), am263px)
APP_SOC_FILES = V2
endif

SRCDIR = . ../Utils ../Utils/$(COMPILER) ../Utils/$(COMPILER)/$(SOC) ../Utils/$(SOC)
SRCDIR += $(autosarConfigSrc_PATH)/Fls_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/src 
SRCDIR += $(autosarConfigSrc_PATH)/Dma_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += soc/$(SOC)/$(CORE)
SRCDIR +=$(mcal_PATH)/Fls/$(APP_SOC_FILES)
SRCDIR +=$(mcal_PATH)/examples/Utils/$(SOC)
SRCDIR +=$(mcal_PATH)/examples/Utils
SRCDIR += $(mcal_PATH)/examples/Flsdiag/soc/$(SOC)/$(CORE)

INCDIR += ../Utils/$(SOC)
INCDIR = .
INCDIR += $(autosarConfigSrc_PATH)/Fls_Demo_Cfg/soc/$(SOC)/$(CORE)/include
INCDIR += $(mcal_PATH)/Fls/include 
INCDIR += $(mcal_PATH)/Fls/$(APP_SOC_FILES)  
INCDIR += $(mcal_PATH)/Fls/src
INCDIR +=$(mcal_PATH)/examples/Utils/$(SOC)
INCDIR += soc/$(SOC)/$(CORE)
INCDIR += $(autosarConfigSrc_PATH)/../examples/Fls
INCDIR += $(autosarConfigSrc_PATH)/../examples/Flsdiag
INCDIR += $(mcal_PATH)/examples/Flsdiag/soc/$(SOC)/$(CORE)

 
INCDIR += $(mcal_PATH)/include/hw/$(PLATFORM) 
INCDIR += $(mcal_PATH)/include/hw
# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig fls mcu port app_utils

INCLUDE_INTERNAL_INTERFACES = flsAppPriv
flsAppPriv_INCLUDE =  $(mcal_PATH)/include $(mcal_PATH)/include/hw/$(SOCFAMILY) $(mcal_PATH)/include/hw

# List all the components required by the application
COMP_LIST_COMMON  =  fls mcu port app_utils

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = Fls_Startup.c Fls_DiagApp.c Fls_NOR_SFDP.c 
SRCS_COMMON += Fls_Cfg.c Fls_PBcfg.c 
SRCS_COMMON += Dem.c Det.c

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

SRCS_ASM_COMMON += sys_startup.asm sys_intvecs.asm

CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS) -D$(SOCFAMILY)

LNKCMD_FILE = ../lnk_r5_$(SOCFAMILY)_$(COMPILER).cmd


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
