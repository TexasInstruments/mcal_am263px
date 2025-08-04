export MCAL_PATH?=$(abspath ../)
export CCS_VERSION?=ccs1281
export AUTOSAR_VERSION?=431

ifeq ($(OS),Windows_NT)
    export ECHO=@echo
    export MAKE=gmake
    export EB_PATH?=C:/EB
    export EB_PATH_SCRIPT=$(EB_PATH)/tresos/bin/tresos_cmd.bat
    export TOOLS_PATH?=C:/ti
    export CCS_PATH?=$(TOOLS_PATH)/$(CCS_VERSION)/ccs
    export CCS_ECLIPSE=$(CCS_PATH)/eclipse/eclipse
    export CYGWIN_PATH?=$(CCS_PATH)/utils/cygwin
    export MKDIR=$(CYGWIN_PATH)/mkdir -p
    export RMDIR=$(CYGWIN_PATH)/rm -rf
    export RM=$(CYGWIN_PATH)/rm -f
    export COPY=$(CYGWIN_PATH)/cp
    export MOVE=$(CYGWIN_PATH)/mv
    export CAT=$(CYGWIN_PATH)/cat
    export SED=$(CYGWIN_PATH)/sed
    export TOUCH=$(CYGWIN_PATH)/touch
    export PATHSEP=\\
    export CHMOD=$(CYGWIN_PATH)/echo
    export SHELL=cmd.exe
    export PWD=cd
    export PYTHON=python
    DOT=$(shell where dot 2>NUL)
else
    UNAME_S := $(shell uname -s)
    ifneq (,$(filter $(UNAME_S),Linux Darwin))
        export ECHO=@echo
        export MAKE=make
        export EB_PATH?=/opt/EB
        export EB_PATH_SCRIPT=$(EB_PATH)/tresos/bin/tresos_cmd.sh
        export TOOLS_PATH?=$(HOME)/ti
        export CCS_PATH?=$(TOOLS_PATH)/$(CCS_VERSION)/ccs
        export CCS_ECLIPSE=$(CCS_PATH)/eclipse/eclipse
        export MKDIR=mkdir -p
        export RMDIR=rm -rf
        export RM=rm -f
        export COPY=cp
        export MOVE=mv
        export CAT=cat
        export SED=sed
        export TOUCH=touch
        export PATHSEP=/
        export CHMOD=chmod
        export PWD=pwd
        export PYTHON=python3
        DOT=$(shell which dot)
    endif
endif

ifeq ($(PLATFORM),$(filter $(PLATFORM), am263 am263x))
  export EB_PLATFORM?=AM263x
  export TI_MCAL_DEVICE?=AM263x
endif
ifeq ($(PLATFORM),$(filter $(PLATFORM), am263px))
  export EB_PLATFORM?=AM263Px
  export TI_MCAL_DEVICE?=AM263Px
endif
ifeq ($(PLATFORM),$(filter $(PLATFORM), am261 am261x))
  export EB_PLATFORM?=AM261x
  export TI_MCAL_DEVICE?=AM261x
endif
