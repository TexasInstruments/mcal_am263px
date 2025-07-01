#*******************************************************************************
#                                                                              *
# Copyright (c) 2022 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# Filename: rules_r5f.mk
#
# Make rules for R5 - This file has all the common rules and defines required
#                     for Cortex-R5 ISA
#
# This file needs to change when:
#     1. Code generation tool chain changes
#     2. Internal switches (which are normally not touched) has to change
#     3. XDC specific switches change
#     4. a rule common for R5 ISA has to be added or modified

CGT_ISA = R5
CGT_EXT = r5f
CGT_PATH = $(TOOLCHAIN_PATH_R5)

# Set compiler/archiver/linker commands and include paths
CODEGEN_INCLUDE = $(TOOLCHAIN_PATH_$(CGT_ISA))/include
ifneq ($(OS),Windows_NT)
CC = $(TOOLCHAIN_PATH_$(CGT_ISA))/LINUX64/bin/dcc
AR = $(TOOLCHAIN_PATH_$(CGT_ISA))/LINUX64/bin/dar
LNK = $(TOOLCHAIN_PATH_$(CGT_ISA))/LINUX64/bin/dld
STRP = $(TOOLCHAIN_PATH_$(CGT_ISA))/LINUX64/bin/striparm
SIZE = $(TOOLCHAIN_PATH_$(CGT_ISA))/LINUX64/bin/sizearm
else
CC = $(TOOLCHAIN_PATH_$(CGT_ISA))\WIN64\bin\dcc.exe
#AR = $(TOOLCHAIN_PATH_$(CGT_ISA))\WIN64\bin\ararm.exe
AR = C:\WindRiver\compilers\llvm-7.0.0.2\WIN64\bin\ararm.exe
LNK = $(TOOLCHAIN_PATH_$(CGT_ISA))\WIN64\bin\dld.exe
STRP = $(TOOLCHAIN_PATH_$(CGT_ISA))\WIN64\bin\striparm.exe
SIZE = $(TOOLCHAIN_PATH_$(CGT_ISA))\WIN64\bin\sizearm.exe
endif

# Derive a part of RTS Library name based on ENDIAN: little/big
ifeq ($(ENDIAN),little)
  RTSLIB_ENDIAN = le
else
  RTSLIB_ENDIAN = be
endif

# Derive compiler switch and part of RTS Library name based on FORMAT: COFF/ELF
ifeq ($(FORMAT),ELF)
  CSWITCH_FORMAT = eabi
  RTSLIB_FORMAT = eabi
endif

#LNKFLAGS_INTERNAL_COMMON += -O4
#LNKFLAGS_INTERNAL_COMMON += --run_linker


# Internal CFLAGS - normally doesn't change
# TODO: Check --fp_mode=strict, --gcc
#CFLAGS_INTERNAL = -c -qq -pdsw225 --endian=$(ENDIAN) -mv7$(CGT_ISA) --fp_mode=strict --abi=$(CSWITCH_FORMAT) -eo.$(OBJEXT) -ea.$(ASMEXT) --symdebug:dwarf --embed_inline_assembly --gcc
#CFLAG internal for DIAB Compiler
# Working   CFLAGS_INTERNAL = -tARMCORTEXR5MH:simple -c -Oz -std=c99 -g -Xassembly-listing -ffunction-sections -fdata-sections -fno-common -fno-builtin -nostdlib
ifeq ($(PROFILE_$(CORE)), release)
CFLAGS_INTERNAL = -tARMCORTEXR5MH:simple -c -0z -std=c99 -Xassembly-listing -ffunction-sections -fdata-sections -fno-common -fno-builtin -nostdlib -DDIAB
else
CFLAGS_INTERNAL = -tARMCORTEXR5MH:simple -c -O0 -std=c99 -g -Xassembly-listing -ffunction-sections -fdata-sections -fno-common -fno-builtin -nostdlib -DDIAB
endif
#ifeq ($(CGT_ISA),$(filter $(CGT_ISA), R5))
#  CFLAGS_INTERNAL += --float_support=vfpv3d16
  # Enabling thumb2 mode
#  CFLAGS_INTERNAL += --code_state=16
#else
#  CFLAGS_INTERNAL += --float_support=vfplib
#endif
#ifeq ($(TREAT_WARNINGS_AS_ERROR), yes)
#  CFLAGS_INTERNAL += --emit_warnings_as_errors
#  LNKFLAGS_INTERNAL_COMMON += --emit_warnings_as_errors
#endif
#CFLAGS_DIROPTS = -fr=$(OBJDIR) -fs=$(OBJDIR)

ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), AM263))
CFLAGS_INTERNAL += -DAM263_PLATFORM
endif



# CFLAGS based on profile selected
#ifeq ($(PROFILE_$(CORE)), debug)
# LNKFLAGS_INTERNAL_PROFILE =
# CFLAGS_INTERNAL += -D_DEBUG_=1
#endif
ifeq ($(PROFILE_$(CORE)), release)
  #LNKFLAGS_INTERNAL_PROFILE = --strict_compatibility=on
  LNKFLAGS_INTERNAL_PROFILE = -qq --diag_warning=225 --diag_suppress=23000 $(LNKFLAGS_GLOBAL_$(CORE))
#  ifeq ($(CGT_ISA),$(filter $(CGT_ISA), R5))
#    CFLAGS_INTERNAL += -ms -O4 -s --optimize_with_debug
#  else
#    CFLAGS_INTERNAL += -ms -op0 -os --inline_recursion_limit=20
#  endif
endif

ifeq ($(JENKINS_TEST_AUTOMATION), TRUE)
CFLAGS_INTERNAL += -DJENKINS_TEST_AUTOMATION
endif

# Following 'if...' block is for an application; to add a #define for each
#   component in the build. This is required to know - at compile time - which
#   components are on which core.
#ifndef MODULE_NAME
  # Derive list of all packages from each of the components needed by the app
  PKG_LIST_R5_LOCAL = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))

  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the local CORE...
#  CFLAGS_APP_DEFINES = $(foreach PKG,$(PKG_LIST_R5_LOCAL),-D_LOCAL_$(PKG)_)
#  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_R5_LOCAL),-D_BUILD_$(PKG)_)

  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the remote CORE...
#  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_R5_REMOTE),-D_REMOTE_$(PKG)_)
#  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_R5_REMOTE),-D_BUILD_$(PKG)_)

#endif

# Assemble CFLAGS from all other CFLAGS definitions
#_CFLAGS = $(CFLAGS_INTERNAL) $(CFLAGS_GLOBAL_$(CORE)) $(CFLAGS_LOCAL_COMMON) $(CFLAGS_LOCAL_$(CORE)) $(CFLAGS_LOCAL_$(PLATFORM)) $(CFLAGS_LOCAL_$(SOCFAMILY)) $(CFLAGS_LOCAL_$(SOC)) $(CFLAGS_APP_DEFINES) $(CFLAGS_COMP_COMMON) $(CFLAGS_GLOBAL_$(PLATFORM))
# Compiler flag for DIAB Compiler
_CFLAGS = $(CFLAGS_INTERNAL) $(CFLAGS_LOCAL_COMMON)
$(info $(_CFLAGS))
# Decide the compile mode
COMPILEMODE= -fc
ifeq ($(CPLUSPLUS_BUILD), yes)
  COMPILEMODE = -fg
endif

# Object file creation
# The first $(CC) generates the dependency make files for each of the objects
# The second $(CC) compiles the source to generate object
$(OBJ_PATHS): $(OBJDIR)/%.$(OBJEXT): %.c
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
#	$(CC) -ppd=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -o $(OBJDIR)/$*.oer5f $<
	$(info $(CC))
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -o $(OBJDIR)/$*.oer5f $<

#TODO: Check ASMFLAGS if really required
#ASMFLAGS = -g --code_state=16 --diag_warning=225 --display_error_number --diag_wrap=off \
			--gen_func_subsections=on --enum_type=packed --auto_inline=0 --small_enum
#TODO: Check ASMFLAGS if really required
#ASMFLAGS = -me -g --code_state=16 --diag_warning=225
#Assembly flag for DIAB Compiler
#ASMFLAGS = -tARMCORTEXR5MH:simple -Xpreprocess-assembly -l -c -g -W:as:.asm
ASMFLAGS = -tARMCORTEXR5MH:simple -c -Oz -g -Xassembly-listing -Xpreprocess-assembly -Werror -W:as:.asm

$(info $(ASMFLAGS))
# Object file creation
$(OBJ_PATHS_ASM): $(OBJDIR)/%.$(OBJEXT): %.asm
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
#	$(CC) -E=$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) $<
	$(CC) $(ASMFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -o $(OBJDIR)/$*.oer5f $<

$(PACKAGE_PATHS): $(PACKAGEDIR)/%: %
	$(ECHO) \# Copying $(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)/$<
	$(MKDIR) -p $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)
	$(CP) --parents -rf $< $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)

# Archive flags - normally doesn't change
ARFLAGS = -cr

#$(info (Obj paths ASM))
#$(info $(OBJ_PATHS_ASM))
#$(info (obj paths))
#$(info $(OBJ_PATHS))
# Archive/library file creation
$(LIBDIR)/$(MODULE_NAME).$(LIBEXT) : $(OBJ_PATHS_ASM) $(OBJ_PATHS)
	$(ECHO) \# Archiving $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(MODULE_NAME): to $@ ...
	$(ECHO) \#
	$(AR) $(ARFLAGS) $@ $(OBJ_PATHS_ASM) $(OBJ_PATHS)

# Linker options and rules
#LNKFLAGS_PRELINK_FLAGS = --silicon_version=7R4
#ifeq ($(PROFILE_$(CORE)), release)
# LNKFLAGS_PRELINK_FLAGS +=  --abi=$(CSWITCH_FORMAT)
#endif
#LNKFLAGS_INTERNAL_COMMON += --emit_warnings_as_errors --diag_error=10247 --diag_error=10423 --display_error_number -w -q -u _c_int00 -c --diag_suppress=10068 -z -a --rom_model --warn_sections --reread_libs --unused_section_elimination=on \
                   --compress_dwarf=on --copy_compression=rle --cinit_compression=rle --reread_libs --disable_auto_rts\
                   --generate_dead_funcs_list=$(BUILD_DIR)\feedback.txt

# Linker options and rules
# --diag_suppress=10068 suppresses warnings about sections missing in linker file
#LNKFLAGS_INTERNAL_COMMON += -w -q -u _c_int00 -c --diag_suppress=10068
#Linker Flag for DIAB Compiler
#LNKFLAGS_INTERNAL_COMMON += -tARMCORTEXR5MH:simple -lc -Xremove-unused-sections -X -Xemulate-gnu-vma-lma
LNKFLAGS_INTERNAL_COMMON += -tARMCORTEXR5MH:simple -Xcheck-overlapping -Xemulate-gnu-vma-lma -Xremove-unused-sections -Xstop-on-redeclaration
LNKFLAGS_INTERNAL_COMMON += -larch -lcdiab -lcdinkum -lllvmc -limpl -lchar -lc


#ifeq ($(CGT_ISA), R5)
#  LNKFLAGS_INTERNAL_COMMON += -mv7R5
  #--diag_suppress=10063 supresses 'warning: entry point other than _c_int00 specified'
#  LNKFLAGS_INTERNAL_COMMON += --diag_suppress=10063
#endif

# Assemble Linker flags from all other LNKFLAGS definitions
#_LNKFLAGS = $(LNKFLAGS_PRELINK_FLAGS) -z $(LNKFLAGS_INTERNAL_COMMON) $(MCAL_LNKFLAGS) $(LNKFLAGS_INTERNAL_PROFILE) $(LNKFLAGS_GLOBAL_$(CORE)) $(LNKFLAGS_LOCAL_COMMON) $(LNKFLAGS_LOCAL_$(CORE))
_LNKFLAGS = $(LNKFLAGS_INTERNAL_COMMON)
$(info $(_LNKFLAGS))
# Path of the RTS library - normally doesn't change for a given tool-chain
#Let the linker choose the required library
ifneq ($(OS),Windows_NT)
RTSLIB_PATH = /home/lte_phy/WindRiver/compilers/diab-7.0.3.0/ARMMH/libcdiab.a
else
#RTSLIB_PATH = C:\WindRiver\compilers\diab-7.0.3.0\ARMMH\libcdiab.a
#RTSLIB_PATH = C:\WindRiver\compilers\diab-7.0.2.1\ARMMH\libcdiab.a
endif
LIB_PATHS += $(RTSLIB_PATH)

#LNK_LIBS = $(addprefix -l,$(LIB_PATHS))
LNK_LIBS += $(addprefix -l,$(EXT_LIB_PATHS))

LNK_LIBS = $(addprefix ,$(LIB_PATHS))
#LNK_LIBS += $(addprefix ,$(EXT_LIB_PATHS))



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

$(info $(EXE_NAME))
$(EXE_NAME) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(LIB_PATHS) $(LNKCMD_FILE)
	$(ECHO) \# Linking into $(EXE_NAME)...
	$(ECHO) \#
	$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS) -o $@ -m6 -@O=$@.map $(LNK_LIBS) $(LNKCMD_FILE)
	$(ECHO) \#
	$(ECHO) \# $@ created.
	$(ECHO) \#

# Include dependency make files that were generated by $(CC)
-include $(SRCS:%.c=$(DEPDIR)/%.P)

# Nothing beyond this point
