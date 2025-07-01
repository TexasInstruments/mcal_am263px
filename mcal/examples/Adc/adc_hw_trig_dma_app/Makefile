APP_NAME = adc_hw_trig_dma_app

ifeq ($(SOC), $(filter $(SOC), am263px))
  ADC_DRV_SOC_FILES = V0
  DMA_DRV_SOC_FILES = V0
  MCU_DRV_SOC_FILES = V2
endif

SRCDIR = . ../../Utils/$(COMPILER) ../../Utils/$(COMPILER)/$(SOC) ../../Utils/$(SOC)
SRCDIR += $(mcal_PATH)/Adc/src $(mcal_PATH)/Adc/$(ADC_DRV_SOC_FILES)
SRCDIR += $(mcal_PATH)/Dma/src $(mcal_PATH)/Dma/$(DMA_DRV_SOC_FILES)
SRCDIR += $(mcal_PATH)/Mcu/src $(mcal_PATH)/Mcu/$(MCU_DRV_SOC_FILES)
SRCDIR += $(mcal_PATH)/include/hw/$(PLATFORM)
SRCDIR += soc/$(SOC)/$(CORE) soc/$(SOC)/tresos/output/src
SRCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/src
SRCDIR += $(mcal_PATH)/examples/Utils/$(SOC)/Pmic

INCDIR = . ../../Utils/$(COMPILER) ../../Utils/$(COMPILER)/$(SOC) ../../Utils/$(SOC)
INCDIR += $(mcal_PATH)/Adc/include $(mcal_PATH)/Adc/src $(mcal_PATH)/Adc/$(ADC_DRV_SOC_FILES)
INCDIR += $(mcal_PATH)/Dma/include $(mcal_PATH)/Dma/src $(mcal_PATH)/Dma/$(DMA_DRV_SOC_FILES)
INCDIR += $(mcal_PATH)/Mcu/include $(mcal_PATH)/Mcu/src $(mcal_PATH)/Mcu/$(MCU_DRV_SOC_FILES)
INCDIR += $(mcal_PATH)/include/memmap
INCDIR += $(mcal_PATH)/include/hw/$(SOCFAMILY) $(mcal_PATH)/include/hw
INCDIR += soc soc/$(SOC)/$(CORE) soc/$(SOC)/tresos/output/include
INCDIR += $(autosarConfigSrc_PATH)/Port_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/include
INCDIR += $(mcal_PATH)/examples/Utils/$(SOC)/Pmic

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW port app_utils
INCLUDE_INTERNAL_INTERFACES =

# List all the components required by the application
COMP_LIST_COMMON = port app_utils

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = AdcApp.c AdcApp_Platform.c
SRCS_COMMON += Port_Cfg.c
SRCS_COMMON += Det.c
ifeq ($(SOC), $(filter $(SOC), am263px))
  SRCS_COMMON += AppPimc.c mcspi_v0.c
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
SRCS_COMMON += Adc.c Adc_Priv.c Adc_Utils.c Adc_Platform.c Adc_Irq.c Adc_PBcfg.c Adc_Cfg.c
SRCS_COMMON += Cdd_Dma.c Cdd_Dma_Irq.c Cdd_Dma_Priv.c Cdd_Dma_soc.c Cdd_Dma_Cfg.c
SRCS_COMMON += Mcu.c Mcu_Priv.c Mcal_Libs_Utils.c Mcu_PBcfg.c Mcu_Cfg.c

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
