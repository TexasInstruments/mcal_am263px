
MODULE_NAME = app_utils

ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/platform.mk

#Accomodating Changes for introducing multiple Tool Chains
SRCDIR = . Intc/$(ARCH) ./$(SOCFAMILY) ./$(COMPILER) ./$(COMPILER)/$(SOC) ./$(SOC)
ifeq ($(PLATFORM), am263)
SRCDIR += $(mcal_PATH)/include/hw/am263
endif
INCDIR = . 
INCDIR += ./$(COMPILER)
INCDIR += ./$(COMPILER)/$(SOC)
INCDIR += ./$(SOC)

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig port spi eth ethtrcv mcu
INCLUDE_INTERNAL_INTERFACES = UtilsPriv
UtilsPriv_INCLUDE =  $(mcal_PATH)/include $(mcal_PATH)/include/hw/$(PLATFORM) $(mcal_PATH)/include/hw

SRCS_COMMON += app_utils.c app_utils_uart.c sci.c trace.c esm.c sys_vim.c Os.c CacheP.c Dem.c boot_armv7r.c MpuP_armv7r.c sys_pmu.c

ifeq ($(PLATFORM), am263)
SRCS_COMMON += app_utilsEth.c
SRCS_COMMON += Mcal_Libs_Utils.c
endif

ifeq ($(PLATFORM), am261)
SRCS_COMMON += app_utilsEth.c
endif

ifeq ($(PLATFORM), am263px)
SRCS_COMMON += app_utilsEth.c
endif

ifeq ($(PLATFORM),$(filter $(PLATFORM), am273 am2732s))
SRCS_COMMON +=appUtils_QSpiFlashLib.c app_utilsEth.c
endif

ifeq ($(MCAL_DYNAMIC_BUILD),TRUE)
  SRCS_COMMON += hw_types.c
  SRCS_COMMON += sys_common.c
endif
ifeq ($(COMPILER),DIAB)
SRCS_ASM_COMMON +=sys_core.asm
SRCS_ASM_COMMON +=sys_startup.asm
SRCS_ASM_COMMON +=sys_intvecs.asm
SRCS_ASM_COMMON +=crt0.asm
else
SRCS_ASM_COMMON +=sys_core.asm boot_armv7r_asm.asm MpuP_armv7r_asm.asm sys_pmu_asm.asm 

endif
PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS) -D$(SOCFAMILY)
ifeq ($(MCAL_DYNAMIC_BUILD),TRUE)
ifeq ($(MCAL_MODULE), Eth)
CFLAGS_LOCAL_COMMON += -DMCAL_DYNAMIC_BUILD_ETH

UtilsPriv_INCLUDE += $(mcal_PATH)/Eth/src/cpsw/include
UtilsPriv_INCLUDE += $(mcal_PATH)/Eth/src/hw
endif
endif

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
