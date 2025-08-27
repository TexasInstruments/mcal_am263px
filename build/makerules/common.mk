#*******************************************************************************
#                                                                              *
# Copyright (c) 2022 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# Filename: common.mk
#
# Common make file - This file has common rules and definitions that are common
#                    across platforms/cores/ISAs/SoCs
#
# This file needs to change when:
#     1. common rule/define has to be added or modified
#

#
# Include make paths and options for all supported targets/platforms
#

ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
ifeq ($(COMPILER),CLANG)
include $(MAKERULEDIR)/build_config_CLANG.mk
endif
include $(MAKERULEDIR)/platform.mk
include $(MAKERULEDIR)/env.mk


.PHONY : all clean gendirs r5f

all : $(CORE)

# Define directories that are going to be created as a part of build process
ifdef MODULE_NAME
  ifeq ($($(MODULE_NAME)_PLATFORM_DEPENDENCY),yes)
    ifeq ($($(MODULE_NAME)_CORE_DEPENDENCY),yes)
      DEPENDENCY_SUB_PATH = $(PLATFORM)/$(CORE)
    else
      DEPENDENCY_SUB_PATH = $(PLATFORM)/$(ISA)
    endif
  else
    ifeq ($($(MODULE_NAME)_CORE_DEPENDENCY),yes)
      DEPENDENCY_SUB_PATH = $(CORE)
    else
      DEPENDENCY_SUB_PATH = $(ISA)
    endif
  endif
endif

ifeq ($(DEST_ROOT),)
 ifdef MODULE_NAME
  OBJDIR = obj/$(DEPENDENCY_SUB_PATH)/$(PROFILE_$(CORE))
  LIBDIR = lib/$(DEPENDENCY_SUB_PATH)/$(PROFILE_$(CORE))
 else
  OBJDIR = obj/$(PLATFORM)/$(CORE)/$(PROFILE_$(CORE))
  BINDIR = bin/$(PLATFORM)
 endif
  PACKAGEDIR = package/$(DEPENDENCY_SUB_PATH)/$(PACKAGE_SELECT)
else
  ifdef MODULE_NAME
    OBJDIR = $(DEST_ROOT)/$($(MODULE_NAME)_RELPATH)/obj/$(DEPENDENCY_SUB_PATH)/$(PROFILE_$(CORE))
    LIBDIR = $(DEST_ROOT)/$($(MODULE_NAME)_RELPATH)/lib/$(DEPENDENCY_SUB_PATH)/$(PROFILE_$(CORE))
  else
     OBJDIR = $(DEST_ROOT)/$(APP_NAME)/obj/$(PLATFORM)/$(CORE)/$(PROFILE_$(CORE))
     BINDIR = $(DEST_ROOT)/$(APP_NAME)/bin/$(PLATFORM)
  endif
  PACKAGEDIR = $(DEST_ROOT/package/$(PACKAGE_SELECT)
endif
DEPDIR = $(OBJDIR)/.deps
DEPFILE = $(DEPDIR)/$(*F)

# Create directories
$(OBJDIR) :
	$(MKDIR) -p $(OBJDIR)

$(DEPDIR) :
	$(MKDIR) -p $(DEPDIR)

$(LIBDIR) :
	$(MKDIR) -p $(LIBDIR)

$(BINDIR) :
	$(MKDIR) -p $(BINDIR)

$(PACKAGEDIR) :
	$(MKDIR) -p $(PACKAGEDIR)

#
# Common variables
#

# Assemble list of source file names
SRCS = $(SRCS_COMMON) $(SRCS_$(CORE)) $(SRCS_$(SOCFAMILY))
SRCS_ASM = $(SRCS_ASM_COMMON) $(SRCS_ASM_$(CORE)) $(SRCS_ASM_$(SOCFAMILY))

ifneq ($(SOCFAMILY),$(PLATFORM))
SRCS += $(SRCS_$(PLATFORM))
SRCS_ASM += $(SRCS_ASM_$(PLATFORM))
endif #ifneq ($(SOCFAMILY,$(PLATFORM))

ifneq ($(SOC),$(SOCFAMILY))
ifneq ($(SOC),$(PLATFORM))
SRCS += $(SRCS_$(SOC))
SRCS_ASM += $(SRCS_ASM_$(SOC))
endif #ifneq ($(SOC),$(PLATFORM))
endif #ifneq ($(SOC),$(SOCFAMILY))

PACKAGE_SRCS = $(PACKAGE_SRCS_COMMON)

# Define search paths
VPATH = $(SRCDIR)

# Following 'if...' block is for an application.
ifndef MODULE_NAME
  # Derive list of all packages from each of the components needed by the app
  PKG_LIST = $(foreach COMP,$(COMP_LIST_COMMON),$($(COMP)_PKG_LIST))
  PKG_LIST += $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))


  # For each of the packages (or modules), get a list of source files that are
  # marked to be compiled in app stage of the build (or in the context in the app)
  SRCS_APPSTG_FILES = $(foreach PKG, $(PKG_LIST), $($(PKG)_APP_STAGE_FILES))
  # The app has to compile package cfg source files in its context. The name
  # of the file assumed is <MOD>_cfg.c under the top-level directory - i.e.
  # specified by <MOD>_PATH variable
  SRCS += $(SRCS_APPSTG_FILES)
  PKG_PATHS = $(foreach PKG,$(PKG_LIST),$($(PKG)_PATH))
  VPATH += $(PKG_PATHS)

  export PKG_LIST
endif

# Change the extension from C to $(OBJEXT) and also add path
OBJ_PATHS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(notdir $(SRCS)))

# Change the extension from ASM to $(OBJEXT) and also add path
OBJ_PATHS_ASM = $(patsubst %.asm, $(OBJDIR)/%.$(OBJEXT), $(SRCS_ASM))

PACKAGE_PATHS = $(patsubst %, $(PACKAGEDIR)/%, $(PACKAGE_SRCS))

# Assemble include paths here
INCLUDE_EXTERNAL = $(foreach INCL,$(INCLUDE_EXTERNAL_INTERFACES),$($(INCL)_INCLUDE))
INCLUDE_INTERNAL = $(foreach INCL,$(INCLUDE_INTERNAL_INTERFACES),$($(INCL)_INCLUDE))
INCLUDE_ALL = $(CODEGEN_INCLUDE) $(INCDIR) $(INCLUDE_EXTERNAL) $(INCLUDE_INTERNAL)

# Add prefix "-I" to each of the include paths in INCLUDE_ALL
INCLUDES = $(addprefix -I,$(INCLUDE_ALL))

# Create rule to "make" all packages
.PHONY : $(PKG_LIST)
$(PKG_LIST) :
	$(ECHO) \# Making $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$@...
	$(MAKE) -C $($@_PATH)

# Get libraries for all the packages
define GET_COMP_DEPENDENCY_SUB_PATH
  ifeq ($$($(1)_PLATFORM_DEPENDENCY),yes)
    ifeq ($$($(1)_CORE_DEPENDENCY),yes)
      $(1)_DEPSUBPATH = $(PLATFORM)/$(CORE)
    else
      $(1)_DEPSUBPATH = $(PLATFORM)/$(ISA)
    endif
   else
    ifeq ($$($(1)_CORE_DEPENDENCY),yes)
      $(1)_DEPSUBPATH = $(CORE)
    else
      $(1)_DEPSUBPATH = $(ISA)
    endif
  endif
endef

$(foreach LIB,$(PKG_LIST),$(eval $(call GET_COMP_DEPENDENCY_SUB_PATH,$(LIB))))

ifeq ($(DEST_ROOT),)
  LIB_PATHS = $(foreach LIB,$(PKG_LIST),$($(LIB)_PATH)/lib/$($(LIB)_DEPSUBPATH)/$(PROFILE_$(CORE))/$(LIB).$(LIBEXT))
else
  LIB_PATHS = $(foreach LIB,$(PKG_LIST),$(DEST_ROOT)/$($(LIB)_RELPATH)/lib/$($(LIB)_DEPSUBPATH)/$(PROFILE_$(CORE))/$(LIB).$(LIBEXT))
endif

# Include make rules for ISA that is built in this iteration
#   eg: rules_m3.mk
# Added makerules for a8 on gcc.
# In case multiple Tool Chains are needed for other cores as well,
# respective EXT for makerules file can be defined here

# Derive GCC EXT makerules file

ifeq ($(TOOLCHAIN_$(ISA)),gcc)
  TOOLCHAINEXT = $(TOOLCHAIN_$(ISA))_
endif


ifeq ($(COMPILER),CLANG)
  include $(MAKERULEDIR)/rules_$(TOOLCHAINEXT)$(ISA).mk
else
  include $(MAKERULEDIR)/rules_$(TOOLCHAINEXT)$(ISA)_$(COMPILER).mk
endif
package : $(PACKAGE_PATHS)

ifdef MODULE_NAME
# Rules for module; this iteration is for a module

# Clean Object and Library (archive) directories
clean :
	$(RM) -rf $(OBJDIR)/* $(DEPDIR)/* $(LIBDIR)/*

# Create dependencies list to ultimately create module archive library file
$(CORE) : $(OBJDIR) $(DEPDIR) $(LIBDIR) $(LIBDIR)/$(MODULE_NAME).$(LIBEXT)


else
# Rules for application; this iteration is for an app

# Clean Object, Binary and Configuro generated directories
clean :
	$(RM) -rf $(OBJDIR)/* $(DEPDIR)/* $(BINDIR)/*

# Create dependencies list to ultimately create application executable binary
$(CORE) : $(OBJDIR) $(BINDIR) $(DEPDIR) $(PKG_LIST)
	$(MAKE) $(EXE_NAME)

endif

# Nothing beyond this point

