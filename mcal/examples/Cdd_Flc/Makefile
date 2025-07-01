APP_NAME = cdd_flc_app

SRCDIR = . ../Utils/$(COMPILER) ../Utils/$(COMPILER)/$(SOC) ../Utils/$(SOC)
SRCDIR += $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/src
SRCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/src
SRCDIR += soc/$(SOC)/$(CORE)

INCDIR = . ../Utils/$(COMPILER) ../Utils/$(COMPILER)/$(SOC) ../Utils/$(SOC)
INCDIR += $(autosarConfigSrc_PATH)/Cdd_Flc_Demo_Cfg/soc/$(SOC)/$(CORE)/include
INCDIR += $(autosarConfigSrc_PATH)/Mcu_Demo_Cfg/soc/$(SOC)/$(CORE)/include
INCDIR += soc soc/$(SOC)/$(CORE)

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig cdd_flc mcu port app_utils

INCLUDE_INTERNAL_INTERFACES = cddFlcAppPriv
cddFlcAppPriv_INCLUDE = $(mcal_PATH)/include/hw/$(SOCFAMILY) $(mcal_PATH)/include/hw

# List all the components required by the application
COMP_LIST_COMMON = cdd_flc mcu port app_utils

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = CddFlcApp.c CddFlcApp_Platform.c
SRCS_COMMON += Mcu_PBcfg.c Mcu_Cfg.c Port_Cfg.c
SRCS_COMMON += Det.c
ifeq ($(SOC), $(filter $(SOC), am261))
  SRCS_COMMON += Port_PBcfg.c
endif
ifeq ($(SOC), $(filter $(SOC), am263px))
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
