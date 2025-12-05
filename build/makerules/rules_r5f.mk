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
CGT_CPU = cortex-r5

# Set compiler/archiver/linker commands and include paths
CODEGEN_INCLUDE = $(TOOLCHAIN_PATH_$(CGT_ISA))/include/c

CC = $(TOOLCHAIN_PATH_$(CGT_ISA))/bin/tiarmclang
AR = $(TOOLCHAIN_PATH_$(CGT_ISA))/bin/tiarmar
LNK = $(TOOLCHAIN_PATH_$(CGT_ISA))/bin/tiarmclang
STRP = $(TOOLCHAIN_PATH_$(CGT_ISA))/bin/tiarmstrip
SIZE = $(TOOLCHAIN_PATH_$(CGT_ISA))/bin/tiarmofd
READELF = $(TOOLCHAIN_PATH_$(CGT_ISA))/bin/tiarmreadelf

# Derive a part of RTS Library name based on ENDIAN: little/big
ifeq ($(ENDIAN),little)
RTSLIB_ENDIAN = le
ENDIAN_NESS = -mlittle-endian
else
RTSLIB_ENDIAN = be
ENDIAN_NESS = -mbig-endian
endif

# Derive compiler switch and part of RTS Library name based on FORMAT: COFF/ELF
ifeq ($(FORMAT),ELF)
CSWITCH_FORMAT = eabi
RTSLIB_FORMAT = eabi
endif

# Internal CFLAGS - normally doesn't change
CFLAGS_INTERNAL = -c $(ENDIAN_NESS) -mcpu=$(CGT_CPU) -gdwarf-3
ifeq ($(CGT_ISA),$(filter $(CGT_ISA), R5))
CFLAGS_INTERNAL += -mfloat-abi=hard -mfpu=vfpv3-d16
# Enabling thumb2 mode
CFLAGS_INTERNAL += -mthumb
endif
ifeq ($(TREAT_WARNINGS_AS_ERROR), false)
CFLAGS_INTERNAL += -Wall
else
CFLAGS_INTERNAL += -Werror -Wall
endif
CFLAGS_INTERNAL += -Wno-gnu-variable-sized-type-not-at-end -Wno-unused-function
LNKFLAGS_INTERNAL_COMMON = -Wl,--emit_warnings_as_errors

ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), am263))
CFLAGS_INTERNAL += -DAM263X_PLATFORM
endif
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), am263px))
CFLAGS_INTERNAL += -DAM263PX_PLATFORM
endif
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), am261))
CFLAGS_INTERNAL += -DAM261X_PLATFORM
endif
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), am263px))
ifeq ($(PACKAGE),SIP)
CFLAGS_INTERNAL += -DAM263PX_SIP_PACKAGE
else
	ifeq ($(PACKAGE),C)
	CFLAGS_INTERNAL += -DAM263PX_C_PACKAGE
	else
	CFLAGS_INTERNAL += -DAM263PX_R_PACKAGE
	endif
endif
endif

# CFLAGS based on profile selected
ifeq ($(PROFILE_$(CORE)), debug)
LNKFLAGS_INTERNAL_PROFILE =
CFLAGS_INTERNAL += -D_DEBUG_=1
endif

LNKFLAGS_INTERNAL_PROFILE = -Wl,-qq $(LNKFLAGS_GLOBAL_$(CORE))

ifeq ($(CGT_ISA),$(filter $(CGT_ISA), R5))
CFLAGS_INTERNAL += -ffunction-sections
else
CFLAGS_INTERNAL += -ms -op0 --inline_recursion_limit=20
endif

ifeq ($(PROFILE_$(CORE)), release)
CFLAGS_INTERNAL += -Os
endif

ifeq ($(JENKINS_TEST_AUTOMATION), TRUE)
CFLAGS_INTERNAL += -DJENKINS_TEST_AUTOMATION
endif

CFLAGS_INTERNAL += -DCLANG

ifeq ($(MCAL_DYNAMIC_BUILD), TRUE)
CFLAGS_INTERNAL += -fprofile-instr-generate -fcoverage-mapping -fmcdc
endif

# -v

# Following 'if...' block is for an application; to add a #define for each
#   component in the build. This is required to know - at compile time - which
#   components are on which core.
ifndef MODULE_NAME
# Derive list of all packages from each of the components needed by the app
PKG_LIST_R5_LOCAL = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))

# Defines for the app and cfg source code to know which components/packages
# are included in the build for the local CORE...
CFLAGS_APP_DEFINES = $(foreach PKG,$(PKG_LIST_R5_LOCAL),-D_LOCAL_$(PKG)_)
CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_R5_LOCAL),-D_BUILD_$(PKG)_)

# Defines for the app and cfg source code to know which components/packages
# are included in the build for the remote CORE...
CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_R5_REMOTE),-D_REMOTE_$(PKG)_)
CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_R5_REMOTE),-D_BUILD_$(PKG)_)
endif

# Assemble CFLAGS from all other CFLAGS definitions
_CFLAGS = $(CFLAGS_INTERNAL) $(CFLAGS_GLOBAL_$(CORE)) $(CFLAGS_LOCAL_COMMON) $(CFLAGS_LOCAL_$(CORE)) $(CFLAGS_LOCAL_$(PLATFORM)) $(CFLAGS_LOCAL_$(SOCFAMILY)) $(CFLAGS_LOCAL_$(SOC)) $(CFLAGS_APP_DEFINES) $(CFLAGS_COMP_COMMON) $(CFLAGS_GLOBAL_$(PLATFORM))

# Decide the compile mode
COMPILEMODE = -x c
ifeq ($(CPLUSPLUS_BUILD), yes)
COMPILEMODE = -x c++
endif

# Object file creation
# The first $(CC) generates the dependency make files for each of the objects
# The second $(CC) compiles the source to generate object
$(OBJ_PATHS): $(OBJDIR)/%.$(OBJEXT): %.c
#	$(ECHO) All flags $(_CFLAGS)
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -M -MF$(DEPFILE).P $(_CFLAGS) $(INCLUDES) $(EXT_CFLAGS) $(EXT_INCS) $(CFLAGS_DIROPTS) $(COMPILEMODE) $<
	$(CC) $(_CFLAGS) $(INCLUDES) $(EXT_CFLAGS) $(EXT_INCS) $(CFLAGS_DIROPTS) $(COMPILEMODE) -o $(OBJDIR)/$*.$(OBJEXT) $<

# Implicitly called with --abi=eabi --object_format=elf --silicon_version=7M4 --float_support=FPv4SPD16 --endian=little --code_state=16 --unaligned_access=on --arm_vmrs_si_workaround=off --embedded_constants=on --hll_source=asm --symdebug:none
ASMFLAGS1 = -mcpu=$(CGT_CPU) -mfloat-abi=hard -mfpu=vfpv3-d16 $(ENDIAN_NESS) -mthumb -save-temps -c
ASMFLAGS2 = -Wti-a,-d=CLANG

# Object file creation
$(OBJ_PATHS_ASM): $(OBJDIR)/%.$(OBJEXT): %.asm
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) $(ASMFLAGS1) -x ti-asm $< $(ASMFLAGS2) -o $(OBJDIR)/$*.$(OBJEXT)

# Object file creation
$(OBJ_PATHS_S): $(OBJDIR)/%.$(OBJEXT): %.S
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) $(ASMFLAGS1) $< -o $(OBJDIR)/$*.$(OBJEXT)

$(PACKAGE_PATHS): $(PACKAGEDIR)/%: %
	$(ECHO) \# Copying $(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)/$<
	$(MKDIR) -p $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)
	$(CP) --parents -rf $< $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)

# Archive flags - normally doesn't change
ARFLAGS = rc

# Archive/library file creation
$(LIBDIR)/$(MODULE_NAME).$(LIBEXT) : $(OBJ_PATHS_ASM) $(OBJ_PATHS_S) $(OBJ_PATHS)
	$(ECHO) \# Archiving $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(MODULE_NAME): to $@ ...
	$(AR) $(ARFLAGS) $@ $(OBJ_PATHS_ASM) $(OBJ_PATHS_S) $(OBJ_PATHS)
	$(ECHO) \# Creating section dump file $(subst .aer5f,,$@)_sections.json ...
	$(ECHO) \#
	$(READELF) --sections --pretty-print --elf-output-style=JSON $@ > $(subst .aer5f,,$@)_sections.json

# Linker options and rules
# --diag_suppress=10068: suppress error "no matching section"
# --diag_suppress=10063: suppress  supresses 'warning: entry point other than _c_int00 specified
LNKFLAGS_INTERNAL_COMMON += -Wl,--warn_sections,-qq,--diag_suppress=10068,-mcpu=$(CGT_CPU),--diag_suppress=10063,--ram_model,--reread_libs
# --diag_suppress=10261: suppress error "section specifier matches no sections"
LNKFLAGS_INTERNAL_COMMON += -Wl,--display_error_number,--diag_suppress=10261

# Assemble Linker flags from all other LNKFLAGS definitions
_LNKFLAGS = $(LNKFLAGS_INTERNAL_COMMON) $(LNKFLAGS_INTERNAL_PROFILE)

LNK_LIBS = $(addprefix -l,$(LIB_PATHS)) $(EXT_LIBS)

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

#BootImage related paths and dependencies

ifeq ($(OS),Windows_NT)
    CCS_ECLIPSE=$(CCS_PATH)/eclipse/ccs-server-cli
    CYGWIN_PATH?=$(CCS_PATH)/utils/cygwin
    MKDIR=$(CYGWIN_PATH)/mkdir -p
    RMDIR=$(CYGWIN_PATH)/rm -rf
    RM=$(CYGWIN_PATH)/rm -f
    COPY=$(CYGWIN_PATH)/cp
    TOUCH=$(CYGWIN_PATH)/touch
    PATHSEP=\\
    CHMOD=$(CYGWIN_PATH)/echo
    SHELL=cmd.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        export CCS_ECLIPSE=$(CCS_PATH)/eclipse/ccs-server-cli.sh
        export MKDIR=mkdir -p
        export RMDIR=rm -rf
        export RM=rm -f
        export COPY=cp
        export TOUCH=touch
        export PATHSEP=/
        export CHMOD=chmod
    endif
endif

CCS_NODE = $(CCS_PATH)/tools/node/node

STRIP=$(CG_TOOL_ROOT)/bin/tiarmstrip
OBJCOPY=$(CG_TOOL_ROOT)/bin/tiarmobjcopy

ifeq ($(OS), Windows_NT)
	MV=$(CYGWIN_PATH)/mv
else
	MV=mv
endif

ifeq ($(OS), Windows_NT)
	PYTHON=python
else
	PYTHON=python3
endif

OUTNAME = $(APP_NAME)_$(CORE)_$(PROFILE_$(CORE))
OUTFILE=$(BINDIR)/$(OUTNAME).$(EXEEXT)
BOOTIMAGE_NAME:=$(OUTNAME).appimage
BOOTIMAGE_NAME_XIP:=$(OUTNAME).appimage_xip
BOOTIMAGE_NAME_SIGNED:=$(OUTNAME).appimage.signed
BOOTIMAGE_RPRC_NAME:=$(OUTNAME)_final.rprc
BOOTIMAGE_RPRC_NAME_XIP:=$(OUTNAME).rprc_xip
BOOTIMAGE_RPRC_NAME_TMP:=$(OUTNAME).rprc_tmp
BOOTIMAGE_INPUT_NAME_MCELF:=$(BINDIR)/$(OUTNAME).xer5f
BOOTIMAGE_NAME_MCELF:=$(BINDIR)/$(OUTNAME).mcelf

# Macros for multicore-elf genimage.py script
MCELF_MERGE_SEGMENTS_FLAG?=true
MCELF_MERGE_SEGMENTS_TOLERANCE_LIMIT?=0
MCELF_IGNORE_CONTEXT_FLAG?=false
MCELF_XIP_RANGE?=0x60000000:0x68000000
# Default am263x address translation JSON is in tools/boot/multicore-elf/deviceData/AddrTranslate/am263x.json
MCELF_ADDR_TRANSLATION_PATH?=""

#Maximum size of a loadable elf segment.
#MCELF_MERGE_SEGMENTS_FLAG should be set to false to achieve this effect.
MCELF_MAX_SEGMENT_SIZE?=8192

#
# Generation of boot image which can be loaded by Secondary Boot Loader (SBL)
#
ifeq ($(OS),Windows_NT)
EXE_EXT=.exe
endif
ifeq ($(OS),Windows_NT)
  BOOTIMAGE_CERT_GEN_CMD=powershell -executionpolicy unrestricted -command $(ROOTDIR)/build/bootimage_scripts/x509CertificateGen.ps1
else
  BOOTIMAGE_CERT_GEN_CMD=$(ROOTDIR)/build/bootimage_scripts/x509CertificateGen.sh
endif
BOOTIMAGE_TEMP_OUT_FILE=$(OUTNAME)_temp.txt

BOOTIMAGE_CORE_ID_r5fss0-0 = 0
BOOTIMAGE_CORE_ID_r5fss0-1 = 1
BOOTIMAGE_CORE_ID_r5fss1-0 = 2
BOOTIMAGE_CORE_ID_r5fss1-1 = 3
SBL_RUN_ADDRESS=0x70002000
SBL_DEV_ID=55

MULTI_CORE_IMAGE_GEN = $(CCS_NODE) $(ROOTDIR)/build/bootimage_scripts/multicoreImageGen.js
OUTRPRC_CMD = $(CCS_NODE) $(ROOTDIR)/build/bootimage_scripts/elf2rprc.js
MCELF_IMAGE_GEN = $(ROOTDIR)/build/bootimage_scripts/multicore-elf/genimage.py

ifeq ($(OS),Windows_NT)
  XIPGEN_CMD=$(ROOTDIR)/build/bootimage_scripts/xipGen.exe
else
  XIPGEN_CMD=$(ROOTDIR)/build/bootimage_scripts/xipGen.out
endif

MULTI_CORE_IMAGE_PARAMS = \
	$(BOOTIMAGE_RPRC_NAME)@$(BOOTIMAGE_CORE_ID_r5fss0-0) \

MULTI_CORE_IMAGE_PARAMS_XIP = \
	$(BOOTIMAGE_RPRC_NAME_XIP)@$(BOOTIMAGE_CORE_ID_r5fss0-0)  \

$(EXE_NAME) : $(OBJ_PATHS_ASM) $(OBJ_PATHS_S) $(OBJ_PATHS) $(LIB_PATHS) $(LNKCMD_FILE)
	$(ECHO) \# Linking into $(EXE_NAME)...
	$(ECHO) \#
	$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS_S) $(OBJ_PATHS) -Wl,--output_file=$@,--map_file=$@.map,$(LNKCMD_FILE) $(LNK_LIBS)
	$(ECHO) \#
	$(ECHO) \# $@ created.
	$(ECHO) \#

ifeq ($(MCELF_ENABLE),yes)
	@echo  Starting MulticoreELF image generation: $(BOOTIMAGE_PATH)/$(BOOTIMAGE_NAME_MCELF) ...
	$(PYTHON) $(MCELF_IMAGE_GEN) --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-0):$(BOOTIMAGE_INPUT_NAME_MCELF) --output=$(BOOTIMAGE_NAME_MCELF) --merge-segments=$(MCELF_MERGE_SEGMENTS_FLAG) --tolerance-limit=$(MCELF_MERGE_SEGMENTS_TOLERANCE_LIMIT) --ignore-context=$(MCELF_IGNORE_CONTEXT_FLAG) --xip=$(MCELF_XIP_RANGE) --xlat=$(MCELF_ADDR_TRANSLATION_PATH) --max_segment_size=$(MCELF_MAX_SEGMENT_SIZE)
	@echo  Boot MulticoreELF ELF image for: $(BOOTIMAGE_PATH)/$(BOOTIMAGE_NAME_MCELF) Done !!!
else
	$(ECHO) \# Starting Boot image generation: $(BOOTIMAGE_NAME)  ...
	$(OUTRPRC_CMD) $(OUTFILE) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(COPY) $(OUTNAME).rprc $(BOOTIMAGE_RPRC_NAME)
	$(COPY) $(BOOTIMAGE_RPRC_NAME) $(BOOTIMAGE_RPRC_NAME_TMP)
	$(RM) $(BOOTIMAGE_RPRC_NAME)
	$(XIPGEN_CMD) -i $(BOOTIMAGE_RPRC_NAME_TMP) -o $(BOOTIMAGE_RPRC_NAME) -x $(BOOTIMAGE_RPRC_NAME_XIP) --flash-start-addr 0x60000000 -v > $(BOOTIMAGE_TEMP_OUT_FILE)
	$(MULTI_CORE_IMAGE_GEN) --devID $(SBL_DEV_ID) --out $(BOOTIMAGE_NAME) $(MULTI_CORE_IMAGE_PARAMS) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(MULTI_CORE_IMAGE_GEN) --devID $(SBL_DEV_ID) --out $(BOOTIMAGE_NAME_XIP) $(MULTI_CORE_IMAGE_PARAMS_XIP) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(RM) $(BOOTIMAGE_RPRC_NAME_TMP)
	$(RM) $(BOOTIMAGE_RPRC_NAME)
	$(RM) $(BOOTIMAGE_TEMP_OUT_FILE)
	$(MV) $(OUTNAME).* $(BINDIR)
	$(ECHO) \# Multicore Boot image generation for: $(BOOTIMAGE_NAME) Done !!!
	$(ECHO) \#
endif


# Include dependency make files that were generated by $(CC)
-include $(SRCS:%.c=$(DEPDIR)/%.P)

# Nothing beyond this point
