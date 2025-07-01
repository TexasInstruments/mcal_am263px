# ======================================================================
#   Copyright (C) 2022-2023 Texas Instruments Incorporated
#
#   All rights reserved. Property of Texas Instruments Incorporated.
#   Restricted rights to use, duplicate or disclose this code are
#   granted through contract.
#
#   The program may not be used without the written permission
#   of Texas Instruments Incorporated or against the terms and conditions
#   stipulated in the agreement under which this program has been
#   supplied.
# ======================================================================

# Filename: Makefile

# This file is the makefile for building ADC example app.

# ======================================================================

APP_NAME = adc_app

ifeq ($(SOC), am263)
APP_SOC_FILES = V0
endif

ifeq ($(SOC), am263px)
APP_SOC_FILES = V0
endif

ifeq ($(SOC), am261)
APP_SOC_FILES = V0
endif

ifeq ($(SOC), am273)
APP_SOC_FILES = V1
endif
SRCDIR = . ../../Utils/$(COMPILER) ../../Utils/$(COMPILER)/$(SOC) ../../Utils/$(SOC)
SRCDIR += $(autosarConfigSrc_PATH)/Adc_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/src

ifeq ($(SOC), am263)
SRCDIR += $(autosarConfigSrc_PATH)/Dma_Demo_Cfg/soc/$(SOC)/$(CORE)/src
endif
ifeq ($(SOC), am261)
SRCDIR += $(autosarConfigSrc_PATH)/Dma_Demo_Cfg/soc/$(SOC)/$(CORE)/src
endif
ifeq ($(SOC), am263px)
SRCDIR += $(autosarConfigSrc_PATH)/Dma_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += $(mcal_PATH)/examples/Utils/$(SOC)/Pmic
endif

SRCDIR += soc/$(SOC)/$(CORE)
INCDIR = .
INCDIR += ../../Utils/$(SOC)
INCDIR += $(autosarConfigSrc_PATH)/Adc_Demo_Cfg/soc/$(SOC)/$(CORE)/include
ifeq ($(SOC), am263)
INCDIR += $(autosarConfigSrc_PATH)/Dma_Demo_Cfg/soc/$(SOC)/$(CORE)/include
endif
ifeq ($(SOC), am261)
INCDIR += $(autosarConfigSrc_PATH)/Dma_Demo_Cfg/soc/$(SOC)/$(CORE)/include
endif
ifeq ($(SOC), am263px)
INCDIR += $(autosarConfigSrc_PATH)/Dma_Demo_Cfg/soc/$(SOC)/$(CORE)/include
endif
INCDIR += $(mcal_PATH)/Adc/include
INCDIR += $(mcal_PATH)/Adc/$(APP_SOC_FILES)
INCDIR += $(mcal_PATH)/Adc/src
INCDIR += soc/$(SOC)/$(CORE)
INCDIR += $(autosarConfigSrc_PATH)/../../examples/Adc
INCDIR += $(mcal_PATH)/include/hw/$(PLATFORM)
INCDIR += $(mcal_PATH)/include/hw
INCDIR += $(mcal_PATH)/examples/Utils/$(SOC)/Pmic

# List all the external components/interfaces, whose interface header files
# need to be included for this component
ifeq ($(SOC), am263)
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig mcu port dma app_utils
endif

ifeq ($(SOC), am261)
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig mcu port dma app_utils
endif

ifeq ($(SOC), am263px)
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig mcu port dma app_utils
endif

ifeq ($(SOC), am273)
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig mcu port app_utils
endif

INCLUDE_INTERNAL_INTERFACES = adcAppPriv
adcAppPriv_INCLUDE = $(mcal_PATH)/include $(mcal_PATH)/include/hw/$(SOCFAMILY) $(mcal_PATH)/include/hw

# List all the components required by the application
ifeq ($(SOC), am263)
COMP_LIST_COMMON = adc dma mcu port app_utils
endif

ifeq ($(SOC), am261)
COMP_LIST_COMMON = adc dma mcu port app_utils
endif

ifeq ($(SOC), am263px)
COMP_LIST_COMMON = adc dma mcu port app_utils pmic
endif

ifeq ($(SOC), am273)
COMP_LIST_COMMON = adc mcu port app_utils
endif

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = AdcApp.c AdcApp_Startup.c

ifeq ($(SOC), am263)
SRCS_COMMON += Adc_PBcfg.c Adc_Cfg.c Port_PBcfg.c Port_Cfg.c Mcu_PBcfg.c Mcu_Cfg.c Cdd_Dma_Cfg.c
endif

ifeq ($(SOC), am261)
SRCS_COMMON += Adc_PBcfg.c Adc_Cfg.c Port_PBcfg.c Port_Cfg.c Mcu_PBcfg.c Mcu_Cfg.c Cdd_Dma_Cfg.c
endif

ifeq ($(SOC), am263px)
  SRCS_COMMON += Adc_PBcfg.c Adc_Cfg.c Mcu_PBcfg.c Mcu_Cfg.c Cdd_Dma_Cfg.c
  SRCS_COMMON += AppPimc.c mcspi_v0.c
  ifeq ($(PACKAGE), SIP)
    SRCS_COMMON += Port_PBcfg_SIP.c
  else
    ifeq ($(PACKAGE), C)
      SRCS_COMMON += Port_PBcfg_C.c
    else
      SRCS_COMMON += Port_PBcfg.c Port_Cfg.c
    endif
  endif
endif

ifeq ($(SOC), am273)

ifeq ($(PLATFORM), am2732s)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am2732s.c Port_Cfg.c
SRCS_COMMON += Adc_PBcfg.c Adc_Cfg.c
endif

ifeq ($(PLATFORM), am273)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am273x.c Port_Cfg.c
SRCS_COMMON += Adc_PBcfg.c Adc_Cfg.c
endif

endif



SRCS_COMMON += Det.c


SRCS_ASM_COMMON += sys_intvecs.asm sys_startup.asm

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
