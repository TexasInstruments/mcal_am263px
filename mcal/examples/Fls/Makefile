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

APP_NAME = fls_app

ifeq ($(SOC), am263)
APP_SOC_FILES = V0
endif

ifeq ($(SOC), am273)
APP_SOC_FILES = V1
endif

ifeq ($(SOC), am2732s)
APP_SOC_FILES = V1
endif

ifeq ($(SOC), am263px)
APP_SOC_FILES = V2
endif

ifeq ($(SOC), am261)
APP_SOC_FILES = V2
endif

ifeq ($(SOC), $(filter $(SOC), am263px))
  I2C_DRV_SOC_FILES = V0
endif

SRCDIR = . ../Utils ../Utils/$(COMPILER) ../Utils/$(COMPILER)/$(SOC) ../Utils/$(SOC)
SRCDIR += $(autosarConfigSrc_PATH)/Fls_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/src 
SRCDIR += $(autosarConfigSrc_PATH)/Dma_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += soc/$(SOC)/$(CORE)
INCDIR += ../Utils/$(COMPILER) ../Utils/$(SOC) ../Utils/$(COMPILER)/$(SOC) ../Utils/$(COMPILER)/$(SOC)
INCDIR += $(autosarConfigSrc_PATH)/Fls_Demo_Cfg/soc/$(SOC)/$(CORE)/include
INCDIR += $(mcal_PATH)/Fls/include 
INCDIR += $(mcal_PATH)/Fls/$(APP_SOC_FILES)  
INCDIR += $(mcal_PATH)/Fls/src
INCDIR += $(mcal_PATH)/Fls/V0 
INCDIR += soc/$(SOC)/$(CORE)
INCDIR += $(autosarConfigSrc_PATH)/../examples/Fls
INCDIR += $(mcal_PATH)/Dma/include 
INCDIR += $(mcal_PATH)/include/hw/$(PLATFORM) 
INCDIR += $(mcal_PATH)/include/hw

ifeq ($(SOC), am263px)
SRCDIR += $(mcal_PATH)/I2c/src $(mcal_PATH)/I2c/$(I2C_DRV_SOC_FILES)
INCDIR += $(mcal_PATH)/I2c/include $(mcal_PATH)/I2c/src $(mcal_PATH)/I2c/$(I2C_DRV_SOC_FILES)
endif
# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig fls mcu port app_utils dma

INCLUDE_INTERNAL_INTERFACES = flsAppPriv
flsAppPriv_INCLUDE =  $(mcal_PATH)/include $(mcal_PATH)/include/hw/$(SOCFAMILY) $(mcal_PATH)/include/hw

# List all the components required by the application
COMP_LIST_COMMON  =  fls mcu port app_utils dma i2c

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = FlsApp.c FlsApp_Startup.c
SRCS_COMMON += Fls_Cfg.c Fls_PBcfg.c 
SRCS_COMMON += Dem.c
ifeq ($(SOC), am263px)
SRCS_COMMON += Cdd_I2c.c Cdd_I2c_Irq.c Cdd_I2c_priv.c
SRCS_COMMON += ioexp_tca6416_6424.c
endif

#ifeq ($(SOC), am273)

ifeq ($(PLATFORM), am2732s)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am2732s.c Port_Cfg.c
endif

ifeq ($(PLATFORM), am273)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am273x.c Port_Cfg.c
endif

#endif

ifeq ($(SOC), am263)
SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_PBcfg.c Port_Cfg.c Cdd_Dma_Cfg.c
endif

ifeq ($(SOC), am261)
SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_PBcfg_Ospi.c Port_Cfg.c Cdd_Dma_Cfg.c
endif

ifeq ($(SOC), am263px)
  SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_Cfg.c Cdd_Dma_Cfg.c
  SRCDIR += $(mcal_PATH)/examples/Utils/am263px/IoMux
  INCDIR += $(mcal_PATH)/examples/Utils/am263px/IoMux
  ifeq ($(PACKAGE), SIP)
    SRCS_COMMON += Port_PBcfg_SIP.c  Cdd_I2c_Cfg.c
    SRCDIR += $(mcal_PATH)/examples/Fls/soc/am263px/tresos/output/src
    INCDIR += soc/$(SOC)/tresos/output/include
  else
    ifeq ($(PACKAGE), C)
      SRCS_COMMON += Port_PBcfg_C.c  Cdd_I2c_Cfg.c
      SRCDIR += $(mcal_PATH)/examples/Fls/soc/am263px/tresos_lp/output/src
      INCDIR += soc/$(SOC)/tresos_lp/output/include
    else
      SRCS_COMMON += Port_PBcfg_Ospi.c  Cdd_I2c_Cfg.c
      SRCDIR += $(mcal_PATH)/examples/Fls/soc/am263px/tresos/output/src
      INCDIR += soc/$(SOC)/tresos/output/include
    endif
  endif
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