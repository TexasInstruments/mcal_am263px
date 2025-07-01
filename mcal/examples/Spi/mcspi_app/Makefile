#******************************************************************************
# Filename: Makefile
#
# This file is the makefile for building SPI example app.
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

APP_NAME = mcspi_app

ifeq ($(SOC),$(filter $(SOC),am263 am263px am261))
APP_SOC_FILES = V0
endif

SRCDIR = . ../../Utils/$(COMPILER) ../../Utils/$(COMPILER)/$(SOC) ../../Utils/$(SOC)
SRCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Spi_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/src

ifeq ($(SOC),$(filter $(SOC),am263 am263px am261))
SRCDIR += $(autosarConfigSrc_PATH)/Dma_Demo_Cfg/soc/$(SOC)/$(CORE)/src
endif

SRCDIR += soc/$(SOC)/$(CORE)

INCDIR = . ../../Utils/$(COMPILER) ../../Utils/$(COMPILER)/$(SOC)
INCDIR += ../../Utils/$(SOC)
INCDIR += soc/$(SOC)/$(CORE)
INCDIR += $(mcal_PATH)/Mcu/$(APP_SOC_FILES)
INCDIR += $(mcal_PATH)/Spi/$(APP_SOC_FILES) 
INCDIR += $(mcal_PATH)/include/hw/$(PLATFORM) 
INCDIR += $(mcal_PATH)/include/hw

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig spi mcu port app_utils dma

INCLUDE_INTERNAL_INTERFACES = spiAppPriv
spiAppPriv_INCLUDE = $(mcal_PATH)/include $(mcal_PATH)/include/hw/$(SOCFAMILY) $(mcal_PATH)/include/hw


ifeq ($(SOC),$(filter $(SOC),am263 am263px am261))
# List all the components required by the application
COMP_LIST_COMMON = spi mcu port app_utils dma
endif

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = McspiApp.c McspiApp_Startup.c
SRCS_COMMON += Spi_PBcfg.c 
SRCS_COMMON += Spi_Lcfg.c
SRCS_COMMON += Spi_Cfg.c
SRCS_COMMON += Dem.c
SRCS_COMMON += Det.c
SRCS_ASM_COMMON += sys_intvecs.asm sys_startup.asm

ifeq ($(SOC), am273)

ifeq ($(PLATFORM), am2732s)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am2732s.c Port_Cfg.c
endif

ifeq ($(PLATFORM), am273)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am273x.c Port_Cfg.c
endif

endif

ifeq ($(SOC), am263)
SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_PBcfg.c Port_Cfg.c Cdd_Dma_Cfg.c
endif

ifeq ($(SOC), am261)
SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_PBcfg.c Port_Cfg.c Cdd_Dma_Cfg.c
endif

ifeq ($(SOC), am263px)
  SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_Cfg.c Cdd_Dma_Cfg.c
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


CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS) -D$(SOCFAMILY)

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
