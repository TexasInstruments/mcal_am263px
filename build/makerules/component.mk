#*******************************************************************************
#                                                                              *
# Copyright (c) 2022 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# File: component.mk
#       This file is component include make file of MCAL/Demo.
# List of variables set in this file and their purpose:
# <mod>_RELPATH        - This is the relative path of the module, typically from
#                        top-level directory of the package
# <mod>_PATH           - This is the absolute path of the module. It derives from
#                        absolute path of the top-level directory (set in env.mk)
#                        and relative path set above
# <mod>_INCLUDE        - This is the path that has interface header files of the
#                        module. This can be multiple directories (space separated)
# <mod>_PKG_LIST       - Names of the modules (and sub-modules) that are a part
#                        part of this module, including itself.
# <mod>_PLATFORM_DEPENDENCY - "yes": means the code for this module depends on
#                             platform and the compiled obj/lib has to be kept
#                             under <platform> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no platform dependent code and hence
#                             the obj/libs are not kept under <platform> dir.
# <mod>_CORE_DEPENDENCY     - "yes": means the code for this module depends on
#                             core and the compiled obj/lib has to be kept
#                             under <core> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no core dependent code and hence
#                             the obj/libs are not kept under <core> dir.
# <mod>_APP_STAGE_FILES     - List of source files that belongs to the module
#                             <mod>, but that needs to be compiled at application
#                             build stage (in the context of the app). This is
#                             primarily for link time configurations or if the
#                             source file is dependent on options/defines that are
#                             application dependent. This can be left blank or
#                             not defined at all, in which case, it means there
#                             no source files in the module <mod> that are required
#                             to be compiled in the application build stage.
#
ifeq ($(component_make_include), )

############################
# device mcal package
# List of components included under mcal lib
# The components included here are built and will be part of mcal lib
############################
mcal_LIB_LIST =

############################
# device mcal application utility packages
# List of application utilities under mcal
# The components included here are built and will be part of mcal app_lib
############################
mcal_APP_LIB_LIST =

############################
# device mcal examples
# List of examples under mcal
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
mcal_EXAMPLE_LIST =

############################
# device kw targets
# List of kw targets 
# All the kw targets mentioned in list are built when allkw target is called
# List below all kw targets for allowed values
############################
mcal_KW_LIST = 

############################
# device mcal examples
# List of examples under mcal
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
mcal_test_EXAMPLE_LIST =
############################
# Duplicate example list which should not be built with "all" (since this is
# duplicate -j option will build both and result in .obj correuption) but needs
# to be still exposed to top level makefile so that user can individually call
# them. Also these duplicate targets doesn't support package option and hence
# should not be included when packaging
############################
mcal_DUP_EXAMPLE_LIST =

# Components included

#include each module component makefile
-include $(mcal_PATH)/mcal_component.mk
ifeq ($(BUILD_OS_TYPE),baremetal)
  ifneq ($(mcal_mcal_LIB_LIST),)
    mcal_LIB_LIST += $(mcal_mcal_LIB_LIST)
  endif
  ifneq ($(mcal_mcal_APP_LIB_LIST),)
    mcal_APP_LIB_LIST += $(mcal_mcal_APP_LIB_LIST)
  endif
  ifneq ($(CDD_IPC_SAFE_ENABLE), yes)
  ifneq ($(mcal_mcal_EXAMPLE_LIST),)
    mcal_EXAMPLE_LIST += $(mcal_mcal_EXAMPLE_LIST)
  endif
  else
  ifneq ($(CDD_IPC_SAFE_EXCEPTION_ENABLE), yes) 
    mcal_EXAMPLE_LIST += ipc_safeipc_app
  else
    mcal_EXAMPLE_LIST += ipc_safeipc_test  
  endif
  endif
  ifneq ($(mcal_mcal_KW_LIST),)
    mcal_KW_LIST += $(mcal_mcal_KW_LIST)
  endif
  ifneq ($(mcal_mcal_DUP_EXAMPLE_LIST),)
    mcal_DUP_EXAMPLE_LIST += $(mcal_mcal_DUP_EXAMPLE_LIST)
  endif
endif

#include each module test component makefile
-include $(mcal_test_PATH)/mcal_test_component.mk
ifeq ($(BUILD_OS_TYPE),baremetal)
  ifneq ($(mcal_mcal_test_EXAMPLE_LIST),)
    mcal_test_EXAMPLE_LIST += $(mcal_mcal_test_EXAMPLE_LIST)
  endif
endif
-include $(mcal_demo_PATH)/mcal_demo_component.mk
ifeq ($(BUILD_OS_TYPE),freertos)
  ifneq ($(mcal_demo_LIB_LIST),)
    mcal_LIB_LIST += $(mcal_demo_LIB_LIST)
  endif
  ifneq ($(mcal_demo_EXAMPLE_LIST),)
    mcal_EXAMPLE_LIST += $(mcal_demo_EXAMPLE_LIST)
  endif
endif

mcal_PKG_LIST_ALL = $(mcal_EXAMPLE_LIST) $(mcal_LIB_LIST) $(mcal_APP_LIB_LIST) $(mcal_test_EXAMPLE_LIST) 

# Component specific CFLAGS
#CFLAGS_COMP_COMMON
MCAL_CFLAGS =
MCAL_LNKFLAGS =

MCAL_LNKFLAGS += --define=-define=ENABLE_ASILB_CHECK

ifeq ($(CORE),$(filter $(CORE), r4))
  MCAL_CFLAGS += -DBUILD_R4
  MCAL_LNKFLAGS += --define=BUILD_R4
endif

ifeq ($(CORE),$(filter $(CORE), r5f))
  MCAL_CFLAGS += -DBUILD_R5F
  MCAL_LNKFLAGS += --define=BUILD_R5F
endif

#Added CFLAG for gcc tool chain, other toolchain cflags can be added here if required

ifeq ($(TOOLCHAIN_$(ISA)),gcc)
MCAL_CFLAGS += -DBUILD_GCC
endif

#Enable trace only for non-Klockwork build and for all profiles
ifeq ($(KW_BUILD),no)
  MCAL_CFLAGS += -DTRACE_ENABLE
endif

# Enable standard asserts for klockwork build
ifeq ($(KW_BUILD),yes)
  MCAL_CFLAGS += -DUSE_STD_ASSERT -DASSERT_ENABLE -DTRACE_ENABLE
endif

ifeq ($(PROFILE_$(CORE)),debug)
  MCAL_CFLAGS += -DDEBUG_BUILD
# Enable asserts for debug build
  MCAL_CFLAGS += -DASSERT_ENABLE
endif

ifeq ($(PROFILE_$(CORE)),release)
  MCAL_CFLAGS += -DRELEASE_BUILD
# Enable asserts for release build
  MCAL_CFLAGS += -DASSERT_ENABLE
endif

ifeq ($(PROFILE_$(CORE)),prod_release)
  MCAL_CFLAGS += -DPROD_RELEASE_BUILD
# Disable asserts for production release
#  MCAL_CFLAGS += -DASSERT_ENABLE
endif

# Add c++ build macro, required to comment out #pragma in library to just check the build,
# This should not be used in actual build
ifeq ($(CPLUSPLUS_BUILD), yes)
  MCAL_CFLAGS += -DMCAL_CPLUSPLUS_BUILD
endif

ifeq ($(MCAL_DYNAMIC_BUILD),TRUE)
  MCAL_CFLAGS += -DMCAL_DYNAMIC_BUILD
endif

ifeq ($(AUTOSAR_VERSION),431)
  MCAL_CFLAGS += -DAUTOSAR_431
endif

ifneq ($(MCAL_TEST_CFLAGS), )
  MCAL_CFLAGS += $(MCAL_TEST_CFLAGS)
endif

ifeq ($(CDD_IPC_SAFE_ENABLE), yes)
  MCAL_CFLAGS += -DSAFE_IPC
endif

export MCAL_LIBS
export MCAL_EXAMPLE_LIBS
export MCAL_CFLAGS
export MCAL_LNKFLAGS

component_make_include := 1
endif

# Nothing beyond this point
