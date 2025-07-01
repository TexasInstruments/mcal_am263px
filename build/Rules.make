ifeq ($(Rules_make_include), )

#Default build environment, Windows_NT or Linux
ifeq ($(OS), )
  OS := Windows_NT
endif

ifeq ($(COMPILER_SELECT), )
  COMPILER :=CLANG
else
  COMPILER :=$(COMPILER_SELECT)
endif

ifeq ($(SOC), )
  SOC := am263px
  PLATFORM := am263px
  export EB_PLATFORM?=AM263Px
endif

ifeq ($(PLATFORM),$(filter $(PLATFORM), am263px))
  SOC = am263px
  export EB_PLATFORM?=AM263Px
  ifeq ($(PACKAGE),SIP)
    PACKAGE = SIP
  else
    ifeq ($(PACKAGE),C)
      PACKAGE = C
    else
      PACKAGE = R
    endif
  endif
endif


ifeq ($(PLATFORM),$(filter $(PLATFORM), am273 am2732s))
  SOC = am273
endif

ifeq ($(PLATFORM),$(filter $(PLATFORM), am261))
  SOC = am261
  export EB_PLATFORM?=AM261x
endif

ifeq ($(CORE), )
  CORE := r5f0_0
endif
export CORE

mcal_RELPATH = mcal
mcal_test_RELPATH = mcal_test
mcal_demo_RELPATH = mcal_demos

# Select to build MCAL & its example applications (baremetal)
# Select to MCAL demo applications (freertos)
# Possible options (freertos/baremetal)
export BUILD_OS_TYPE ?= baremetal

ifeq ($(OS),Windows_NT)
  # Paths for windows machine
    CCS_PATH := C:/ti/ccs1281/ccs
    export EB_PATH?=C:/EB
else
    CCS_PATH := /opt/ti/ccs1281/ccs
    export EB_PATH?=/opt/EB
endif

ifeq ($(OS),Windows_NT)
  # Paths for windows machine
  ifeq ($(COMPILER),TI_COMPILER)
    TOOLCHAIN_PATH_R5 := $(CCS_PATH)/tools/compiler/ti-cgt-arm_20.2.7.LTS
  else
    ifeq ($(PLATFORM),$(filter $(PLATFORM), am263 am263px am261))
      TOOLCHAIN_PATH_R5 := C:/ti/ti-cgt-armllvm_4.0.1.LTS
    else
      TOOLCHAIN_PATH_R5 := C:/ti/ti-cgt-armllvm_2.1.3.LTS
    endif
  endif
else
  #Paths for linux machine
  ifeq ($(COMPILER),TI_COMPILER)
    TOOLCHAIN_PATH_R5 := /opt/ti/ti-cgt-arm_18.12.2.LTS
  else
    ifeq ($(PLATFORM),$(filter $(PLATFORM), am263 am263px am261))
      TOOLCHAIN_PATH_R5 := /opt/ti/ti-cgt-armllvm_4.0.1.LTS
    else
      TOOLCHAIN_PATH_R5 := /opt/ti/ti-cgt-armllvm_2.1.3.LTS
    endif
  endif
endif

mcal_PATH := $(abspath ..)/$(mcal_RELPATH)
mcal_test_PATH := $(abspath ..)/$(mcal_test_RELPATH)
mcal_demo_PATH := $(abspath ..)/$(mcal_demo_RELPATH)

ifeq ($(BUILD_OS_TYPE),baremetal)
  export autosarConfigSrc_PATH ?= $(mcal_PATH)/examples_config
else
  export autosarConfigSrc_PATH ?= $(mcal_demo_PATH)
endif

#Autosar basic software include path provided by AUTOSAR stack
autosarBSWInc_PATH := $(mcal_PATH)/autosar_include

#Default MCAL config - use base directory
MCAL_CONFIG ?= 0
CDD_IPC_SAFE_ENABLE ?= no
CDD_IPC_SAFE_EXCEPTION_ENABLE ?= no
# Get config path for each component
ifeq ($(CDD_IPC_SAFE_ENABLE),no)
  MCAL_COMP_DIR_LIST = Mcu Port Gpt Spi Can Cdd_Cmpss Cdd_Flc Ipc Dio Wdg Fls Eth EthTrcv Adc Pwm Icu Uart Dma I2c FsiTx FsiRx Lin Epwm
  define GET_MCAL_COMP_CONFIG_PATH
    # MCAL_MODULE is passing through gmake command as argument
    ifeq ($(MCAL_MODULE),$(1))
  	$(1)_CONFIG_PATH = $(mcal_test_PATH)/ut_config/$(1)/soc/$(SOC)/$(CORE)/config_$(MCAL_CONFIG)
    else
  	ifeq ($(PLATFORM),am2732s)
  	  ifeq ($(1),Port)
  	    $(1)_CONFIG_PATH += $(autosarConfigSrc_PATH)/$(1)_Demo_Cfg/soc/$(PLATFORM)/$(CORE)/include
        else
  	    $(1)_CONFIG_PATH += $(autosarConfigSrc_PATH)/$(1)_Demo_Cfg/soc/$(SOC)/$(CORE)/include
        endif
      endif
  	ifeq ($(PLATFORM),$(filter $(PLATFORM), am263 am273 am263px am261))
  	  $(1)_CONFIG_PATH += $(autosarConfigSrc_PATH)/$(1)_Demo_Cfg/soc/$(SOC)/$(CORE)/include
      endif
    endif
  endef
else
  MCAL_COMP_DIR_LIST = Mcu Port Ipc Eth EthTrcv Spi
  define GET_MCAL_COMP_CONFIG_PATH
    $(1)_CONFIG_PATH += $(autosarConfigSrc_PATH)/$(1)_Demo_Cfg/soc/$(SOC)/$(CORE)/include
    ifeq ($(CDD_IPC_SAFE_EXCEPTION_ENABLE),no)
      $(1)_CONFIG_PATH +=  $(autosarConfigSrc_PATH)/SafeIpc_Demo_Cfg/soc/$(SOC)/$(CORE)/include
    else
      ifeq ($(PLATFORM),am263)
        $(1)_CONFIG_PATH +=  $(autosarConfigSrc_PATH)/SafeIpc_Exception_Demo_Cfg/soc/$(SOC)/$(CORE)/include
      endif
    endif
  endef
endif
$(foreach MCAL_COMP,$(MCAL_COMP_DIR_LIST),$(eval $(call GET_MCAL_COMP_CONFIG_PATH,$(MCAL_COMP))))

#Autosar generated config include files
#Can be list of directories separated by space.
#Should include path to each modules pre compile header path
#Should include path to each modules <Mod>_Memmap.h
autosarConfig_PATH = $(foreach MCAL_COMP,$(MCAL_COMP_DIR_LIST),$($(MCAL_COMP)_CONFIG_PATH))
autosarConfig_PATH += $(mcal_PATH)/include/memmap

# Utilities directory. This is required only if the build machine is Windows.
#   - specify the installation directory of utility which supports POSIX commands
#     (eg: Cygwin installation or MSYS installation).
ifeq ($(OS),Windows_NT)
  UTILS_INSTALL_DIR := $(CCS_PATH)/utils/cygwin
  GMAKE_DIR := $(CCS_PATH)/utils/cygwin
else
  UTILS_INSTALL_DIR := $(CCS_PATH)/utils/bin
  GMAKE_DIR := $(CCS_PATH)/utils/bin
endif

ROOTDIR := $(abspath ..)

# Default platform
  PLATFORM := am263px
# Supported values: am263


# Default Profile
# Supported Values: debug | release | prod_release
ifeq ($(PROFILE), )
  PROFILE := release
endif

# Default Build Variant
# Supported Values: precompile | linktime | postbuild
ifeq ($(BUILD_VARIANT), )
  BUILD_VARIANT := precompile
endif

# Set Core Profile depending on PROFILE value
ifeq ($(PROFILE_$(CORE)), )
  PROFILE_$(CORE) := $(PROFILE)
endif

# Default klockwork build flag, yes or no
ifeq ($(KW_BUILD), )
  KW_BUILD := no
endif

# Default C++ build flag, yes or no
ifeq ($(CPLUSPLUS_BUILD), )
  CPLUSPLUS_BUILD := no
endif

# Default Warnings as Errors flag, yes or no
ifeq ($(TREAT_WARNINGS_AS_ERROR), )
  TREAT_WARNINGS_AS_ERROR := yes
endif

# Default AUTOSAR Version
ifeq ($(AUTOSAR_VERSION), )
  AUTOSAR_VERSION := 431
endif


# Default MCELF generation is off
ifeq ($(MCELF_ENABLE), )
  MCELF_ENABLE := no
endif

# Enable dynamic analysis build. This is used to define HW macros as global
# functions so that it doesn't come in dynamic report as not covered
MCAL_DYNAMIC_BUILD ?= FALSE

export OS
export COMPILER
export PLATFORM
export SOC
export PROFILE
export PROFILE_$(CORE)
export TOOLCHAIN_PATH_R5
export mcal_RELPATH
export mcal_PATH
export mcal_test_PATH
export mcal_demo_PATH
export ROOTDIR
export UTILS_INSTALL_DIR
export GMAKE_DIR
export KW_BUILD
export CPLUSPLUS_BUILD
export autosarBSWInc_PATH
export TREAT_WARNINGS_AS_ERROR
export autosarConfig_PATH
export MCAL_CONFIG
export MCAL_DYNAMIC_BUILD
export AUTOSAR_VERSION
export CCS_PATH

Rules_make_include := 1
endif

ifeq ($(MAKERULEDIR), )
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif

ifeq ($(COMPILER),CLANG)
include $(MAKERULEDIR)/build_config_CLANG.mk
else
include $(MAKERULEDIR)/build_config.mk
endif
include $(MAKERULEDIR)/platform.mk
include $(MAKERULEDIR)/env.mk
include $(MAKERULEDIR)/component.mk