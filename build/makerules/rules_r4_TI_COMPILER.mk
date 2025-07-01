#*******************************************************************************
#                                                                              *
# Copyright (c) 2022 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# Filename: rules_r4.mk
#
# Make rules for R4 - This file has all the common rules and defines required
#                     for Cortex-R4 ISA
#
# This file needs to change when:
#     1. Code generation tool chain changes (currently it uses TMS470)
#     2. Internal switches (which are normally not touched) has to change
#     3. XDC specific switches change
#     4. a rule common for R4 ISA has to be added or modified

# Set compiler/archiver/linker commands and include paths
CODEGEN_INCLUDE = $(CODEGEN_PATH_R4)/include \
                  $(CODEGEN_PATH_R4)/include/AUTOSAR31
CC = $(CODEGEN_PATH_R4)/bin/armcl
AR = $(CODEGEN_PATH_R4)/bin/armar
# Need to run armcl with --run_linker option
LNK = $(CODEGEN_PATH_R4)/bin/armcl

# Derive a part of RTS Library name based on ENDIAN: little/big
ifeq ($(ENDIAN),little)
  RTSLIB_ENDIAN = le
else
  RTSLIB_ENDIAN = be
endif

# Derive compiler switch and part of RTS Library name based on FORMAT: COFF/ELF
ifeq ($(FORMAT),COFF)
  CSWITCH_FORMAT = ti_arm9_abi
  RTSLIB_FORMAT = tiarm9
endif
ifeq ($(FORMAT),ELF)
  CSWITCH_FORMAT = eabi
  RTSLIB_FORMAT = eabi
endif

# Internal CFLAGS - normally doesn't change
CFLAGS_INTERNAL = -c -qq -pdsw225 --$(ENDIAN)_endian -mv7R4 --code_state=16 --float_support=VFPv3D16 --fp_mode=strict --abi=$(CSWITCH_FORMAT) -eo.$(OBJEXT) -ea.$(ASMEXT) --symdebug:dwarf --embed_inline_assembly --gcc
ifeq ($(TREAT_WARNINGS_AS_ERROR), yes)
CFLAGS_INTERNAL += --emit_warnings_as_errors
endif
CFLAGS_DIROPTS = -fr=$(OBJDIR) -fs=$(OBJDIR)

# CFLAGS based on profile selected
ifeq ($(PROFILE_$(CORE)), debug)
 LNKFLAGS_INTERNAL_PROFILE =
 CFLAGS_INTERNAL += -D_DEBUG_=1
endif
ifeq ($(PROFILE_$(CORE)), release)
 LNKFLAGS_INTERNAL_PROFILE = --strict_compatibility=on
 #CFLAGS_INTERNAL += --opt_level=3 --optimize_with_debug --inline_recursion_limit=20
 CFLAGS_INTERNAL += --optimize_with_debug --inline_recursion_limit=20

endif

# Following 'if...' block is for an application; to add a #define for each
#   component in the build. This is required to know - at compile time - which
#   components are on which core.
ifndef MODULE_NAME
  # Derive list of all packages from each of the components needed by the app
  PKG_LIST_R4_LOCAL = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))

  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the local CORE...
  CFLAGS_APP_DEFINES = $(foreach PKG,$(PKG_LIST_R4_LOCAL),-D_LOCAL_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_R4_LOCAL),-D_BUILD_$(PKG)_)

  ifeq ($(CORE),r4)
    PKG_LIST_R4_REMOTE = $(foreach COMP,$(COMP_LIST_ipu1_1),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_ipu1_0_
  endif

  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the remote CORE...
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_R4_REMOTE),-D_REMOTE_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_R4_REMOTE),-D_BUILD_$(PKG)_)

endif

# Assemble CFLAGS from all other CFLAGS definitions
_CFLAGS = $(CFLAGS_INTERNAL) $(CFLAGS_GLOBAL_$(CORE)) $(CFLAGS_LOCAL_COMMON) $(CFLAGS_LOCAL_$(CORE)) $(CFLAGS_LOCAL_$(PLATFORM)) $(CFLAGS_LOCAL_$(SOCFAMILY)) $(CFLAGS_LOCAL_$(SOC)) $(CFLAGS_APP_DEFINES) $(CFLAGS_COMP_COMMON) $(CFLAGS_GLOBAL_$(PLATFORM))

# Decide the compile mode
COMPILEMODE = -fc
ifeq ($(CPLUSPLUS_BUILD), yes)
  COMPILEMODE = -fg
endif

# Object file creation
# The first $(CC) generates the dependency make files for each of the objects
# The second $(CC) compiles the source to generate object
$(OBJ_PATHS): $(OBJDIR)/%.$(OBJEXT): %.c
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $(COMPILEMODE) $<
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $(COMPILEMODE) $<

#TODO: Check ASMFLAGS if really required
ASMFLAGS = -g --code_state=16 --diag_warning=225 --display_error_number --diag_wrap=off \
			--gen_func_subsections=on --enum_type=packed --auto_inline=0 --small_enum

# Object file creation
$(OBJ_PATHS_ASM): $(OBJDIR)/%.$(OBJEXT): %.asm
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fa $<
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -fa $<

$(PACKAGE_PATHS): $(PACKAGEDIR)/%: %
	$(ECHO) \# Copying $(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)/$<
	$(MKDIR) -p $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)
	$(CP) --parents -rf $< $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)

# Archive flags - normally doesn't change
ARFLAGS = rq

# Archive/library file creation
$(LIBDIR)/$(MODULE_NAME).$(LIBEXT) : $(OBJ_PATHS_ASM) $(OBJ_PATHS)
	$(ECHO) \# Archiving $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(MODULE_NAME): to $@ ...
	$(ECHO) \#
	$(AR) $(ARFLAGS) $@ $(OBJ_PATHS_ASM) $(OBJ_PATHS)

# Linker options and rules
LNKFLAGS_PRELINK_FLAGS = --silicon_version=7R4
ifeq ($(PROFILE_$(CORE)), release)
 LNKFLAGS_PRELINK_FLAGS +=  --abi=$(CSWITCH_FORMAT)
endif
LNKFLAGS_INTERNAL_COMMON += --emit_warnings_as_errors --diag_error=10247 --diag_error=10423 --display_error_number -w -q -u _c_int00 -c --diag_suppress=10068 -z -a --rom_model --warn_sections --reread_libs --unused_section_elimination=on \
                   --compress_dwarf=on --copy_compression=rle --cinit_compression=rle --reread_libs --disable_auto_rts\
                   --generate_dead_funcs_list=$(BUILD_DIR)\feedback.txt

# Assemble Linker flags from all other LNKFLAGS definitions
_LNKFLAGS = $(LNKFLAGS_PRELINK_FLAGS) -z $(LNKFLAGS_INTERNAL_COMMON) $(MCAL_LNKFLAGS) $(LNKFLAGS_INTERNAL_PROFILE) $(LNKFLAGS_GLOBAL_$(CORE)) $(LNKFLAGS_LOCAL_COMMON) $(LNKFLAGS_LOCAL_$(CORE))

# Path of the RTS library - normally doesn't change for a given tool-chain
#RTSLIB_PATH = $(CODEGEN_PATH_M4)/lib/rtsv7M4_T_$(RTSLIB_ENDIAN)_$(RTSLIB_FORMAT).lib
#Let the linker choose the required library
RTSLIB_PATH = $(CODEGEN_PATH_R4)/lib/libc.a
LIB_PATHS += $(RTSLIB_PATH)

LNK_LIBS = $(addprefix -l,$(LIB_PATHS))
# Linker - to create executable file

ifeq ($(LOCAL_APP_NAME),)
 EXE_NAME = $(BINDIR)/$(APP_NAME)_$(CORE)_$(PROFILE_$(CORE)).$(EXEEXT)
else
 ifeq ($(PROFILE_$(CORE)),prod_release)
  EXE_NAME = $(BINDIR)/$(LOCAL_APP_NAME).$(EXEEXT)
 else
  EXE_NAME = $(BINDIR)/$(LOCAL_APP_NAME)_$(PROFILE_$(CORE)).$(EXEEXT)
 endif
endif

$(EXE_NAME) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(LIB_PATHS) $(LNKCMD_FILE)
	$(ECHO) \# Linking into $(EXE_NAME)...
	$(ECHO) \#
	$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(LNKCMD_FILE) -o $@ -m $@.map $(LNK_LIBS)
	$(ECHO) \#
	$(ECHO) \# $@ created.
	$(ECHO) \#

# Include dependency make files that were generated by $(CC)
-include $(SRCS:%.c=$(DEPDIR)/%.P)

# Nothing beyond this point
