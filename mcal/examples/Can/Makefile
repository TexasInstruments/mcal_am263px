# Filename: Makefile
#
# This file is the makefile for building CAN example app.
#
#   Copyright (c) 2023 Texas Instruments Incorporated
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

APP_NAME = can_app

ifeq ($(SOC), $(filter $(SOC), am263 am263px am261 am273))
  I2C_DRV_SOC_FILES = V0
endif

SRCDIR = . ../Utils ../Utils/$(COMPILER) ../Utils/$(COMPILER)/$(SOC) ../Utils/$(SOC)
SRCDIR += $(mcal_PATH)/I2c/src $(mcal_PATH)/I2c/$(I2C_DRV_SOC_FILES)
SRCDIR += $(autosarConfigSrc_PATH)/Can_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += soc/$(SOC)/$(CORE)
ifeq ($(SOC), am263px)
  SRCDIR += $(mcal_PATH)/examples/Utils/am263px/Pmic
  SRCDIR += $(mcal_PATH)/examples/Utils/am263px/IoMux
endif
INCDIR = .
INCDIR = ../Utils/$(SOC)
INCDIR += ./soc/$(SOC)/$(CORE)
INCDIR += $(mcal_PATH)/I2c/include $(mcal_PATH)/I2c/src $(mcal_PATH)/I2c/$(I2C_DRV_SOC_FILES)
INCDIR += $(autosarConfigSrc_PATH)/Can_Demo_Cfg/soc/$(SOC)/$(CORE)/include
INCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/include
INCDIR += $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/include

ifeq ($(SOC), am263px)
  INCDIR += $(mcal_PATH)/examples/Utils/am263px/Pmic
  INCDIR += $(mcal_PATH)/examples/Utils/am263px/IoMux
endif
INCDIR += $(mcal_PATH)/include/memmap
INCDIR += $(mcal_PATH)/include/hw/$(PLATFORM)
INCDIR += $(mcal_PATH)/include/hw

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW can mcu port app_utils fls

INCLUDE_INTERNAL_INTERFACES = canAppPriv
canAppPriv_INCLUDE = $(mcal_PATH)/include $(mcal_PATH)/include/hw/$(SOCFAMILY) $(mcal_PATH)/include/hw

# List all the components required by the application
COMP_LIST_COMMON = can mcu port app_utils

ifeq ($(SOC), am263px)
  SRCS_COMMON = ioexp_tca6416_6424.c
endif

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += CanApp.c CanApp_Startup.c Can_Cfg.c Can_PBcfg.c
SRCS_ASM_COMMON += sys_intvecs.asm sys_startup.asm
SRCS_COMMON += Dem.c
SRCS_COMMON += Cdd_I2c.c Cdd_I2c_Irq.c Cdd_I2c_priv.c

ifeq ($(SOC), am273)
  SRCDIR += $(autosarConfigSrc_PATH)/I2c_Demo_Cfg/soc/$(SOC)/$(CORE)/src
  INCDIR += $(autosarConfigSrc_PATH)/I2c_Demo_Cfg/soc/$(SOC)/$(CORE)/include
ifeq ($(PLATFORM), am2732s)
  SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am2732s.c Port_Cfg.c Cdd_I2c_Cfg.c
endif
ifeq ($(PLATFORM), am273)
  SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am273x.c Port_Cfg.c Cdd_I2c_Cfg.c
endif
endif

ifeq ($(SOC), am263)
  SRCDIR += $(autosarConfigSrc_PATH)/I2c_Demo_Cfg/soc/$(SOC)/$(CORE)/src
  INCDIR += $(autosarConfigSrc_PATH)/I2c_Demo_Cfg/soc/$(SOC)/$(CORE)/include
  SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_PBcfg.c Port_Cfg.c Cdd_I2c_Cfg.c
endif

ifeq ($(SOC), am261)
  SRCDIR += $(autosarConfigSrc_PATH)/I2c_Demo_Cfg/soc/$(SOC)/$(CORE)/src
  INCDIR += $(autosarConfigSrc_PATH)/I2c_Demo_Cfg/soc/$(SOC)/$(CORE)/include
  SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_PBcfg.c Port_Cfg.c Cdd_I2c_Cfg.c
endif

ifeq ($(SOC), am263px)
  SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_Cfg.c
  SRCS_COMMON += AppPimc.c mcspi_v0.c
  INCDIR += $(autosarConfigSrc_PATH)/Fls_Demo_Cfg/soc/$(SOC)/$(CORE)/include
  ifeq ($(PACKAGE), SIP)
    SRCDIR += soc/$(SOC)/tresos/output/src
    INCDIR += soc/$(SOC)/tresos/output/include
    SRCS_COMMON += Port_PBcfg_SIP.c Cdd_I2c_Cfg.c
  else
    ifeq ($(PACKAGE), C)
	  SRCDIR += soc/$(SOC)/tresos_lp/output/src
      INCDIR += soc/$(SOC)/tresos_lp/output/include
      SRCS_COMMON += Port_PBcfg_C.c Cdd_I2c_Cfg.c
    else
	  SRCDIR += soc/$(SOC)/tresos/output/src
      INCDIR += soc/$(SOC)/tresos/output/include
      SRCS_COMMON += Port_PBcfg_CAN.c Cdd_I2c_Cfg.c
    endif
  endif
endif

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
