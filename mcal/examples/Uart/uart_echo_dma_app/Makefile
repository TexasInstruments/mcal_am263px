# Filename: Makefile
#
# This file is the makefile for building UART Echo example app with DMA mode.
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
# ******************************************************************************

APP_NAME = uart_echo_dma_app

# Sources
SRCDIR = . ../../Utils/$(COMPILER) ../../Utils/$(COMPILER)/$(SOC) ../../Utils/$(SOC) \
         $(autosarConfigSrc_PATH)/Uart_Demo_Cfg/soc/$(SOC)/$(CORE)/src  \
         $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/src \
         $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/src  \
         $(autosarConfigSrc_PATH)/Dma_Demo_Cfg/soc/$(SOC)/$(CORE)/src \
         $(mcal_PATH)/Uart/$(SOC_FILES) $(mcal_PATH)/Uart/src soc/$(SOC)/$(CORE)

INCDIR = . $(mcal_PATH)/examples/Config $(mcal_PATH)/include \
           $(mcal_PATH)/include/hw $(mcal_PATH)/Dma/config \
           $(mcal_PATH)/include/hw/$(PLATFORM) ../../Utils/$(COMPILER) ../../Utils/$(SOC) ../../Utils/$(COMPILER)/$(SOC) \
           $(mcal_PATH)/Uart/$(SOC_FILES) $(mcal_PATH)/Uart/include soc/$(SOC)/$(CORE) \
		   
# List all the components required by the application
ifeq ($(SOC),$(filter $(SOC),am263 am263px am273 am2732s))
COMP_LIST_COMMON = uart dma mcu port app_utils
endif

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig app_utils

INCLUDE_INTERNAL_INTERFACES = $(COMP_LIST_COMMON)

EXT_CFLAGS = -DSOC_AM263X

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = Cdd_Uart_Cfg.c Cdd_Uart_PBcfg.c UartEchoDma.c UartEchoDma_Startup.c
SRCS_COMMON += Dem.c Det.c

ifeq ($(SOC), am273)

ifeq ($(PLATFORM), am2732s)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am2732s.c Port_Cfg.c Cdd_Dma_Cfg.c
endif

ifeq ($(PLATFORM), am273)
SRCS_COMMON += Mcu_PBcfg_am273x.c Mcu_Cfg.c Port_PBcfg_am273x.c Port_Cfg.c Cdd_Dma_Cfg.c
endif

endif

ifeq ($(SOC), am263)
SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_PBcfg_UART0.c Cdd_Dma_Cfg.c
endif

ifeq ($(SOC), am263px)
  SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Cdd_Dma_Cfg.c
  ifeq ($(PACKAGE), SIP)
    SRCS_COMMON += Port_PBcfg_UART0.c
  else
    SRCS_COMMON += Port_PBcfg_UART0.c
  endif
endif

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
