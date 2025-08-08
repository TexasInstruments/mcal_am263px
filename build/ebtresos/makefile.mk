export MCAL_PATH := $(abspath ../../)
include $(MCAL_PATH)/build/imports.mk

.PHONY: all clean copy_plugins delete_plugins move_plugins moveback_plugins build_project make_dir rm_dir import_project generate_project delete_project

export EB_PROJECT_NAME?=None
export EB_PROJECT_PATH?=None
export EB_WORKSPACE?=$(MCAL_PATH)/build/ebtresos/eb_workspace/$(EB_PROJECT_NAME)
export EB_BACKUP?=$(MCAL_PATH)/build/ebtresos/eb_backup
export EB_OUTPUT_PATH?=$(EB_PROJECT_PATH)
export EB_EXTRA_OUTPUT_PATH?=$(EB_OUTPUT_PATH)
export PACKAGE?=None

all: build_project

clean: delete_project

build_project: generate_project delete_project

copy_plugins: delete_plugins
	$(ECHO) Copying TI Plugins to EB Tresos plugins folder for $(EB_PLATFORM) ...
	$(COPY) -rf $(MCAL_PATH)/mcal_config/plugins/$(EB_PLATFORM)/*_TI_$(EB_PLATFORM) $(EB_PATH)/tresos/plugins/
ifeq ($(PACKAGE),$(filter $(PACKAGE), C))
	$(RMDIR) $(EB_PATH)/tresos/plugins/Port_TI_$(EB_PLATFORM)
	$(RMDIR) $(EB_PATH)/tresos/plugins/EthTrcv_TI_$(EB_PLATFORM)
	$(COPY) -rf $(MCAL_PATH)/mcal_config/plugins/$(EB_PLATFORM)/Port_TI_$(EB_PLATFORM)_C $(EB_PATH)/tresos/plugins/
	$(COPY) -rf $(MCAL_PATH)/mcal_config/plugins/$(EB_PLATFORM)/EthTrcv_TI_$(EB_PLATFORM)_C $(EB_PATH)/tresos/plugins/
endif
ifeq ($(PACKAGE),$(filter $(PACKAGE), SIP))
	$(RMDIR) $(EB_PATH)/tresos/plugins/Port_TI_$(EB_PLATFORM)
	$(COPY) -rf $(MCAL_PATH)/mcal_config/plugins/$(EB_PLATFORM)/Port_TI_$(EB_PLATFORM)_SIP $(EB_PATH)/tresos/plugins/
endif

delete_plugins:
	$(ECHO) Deleting TI Plugins from EB Tresos plugins folder for $(EB_PLATFORM) ...
	$(RMDIR) $(EB_PATH)/tresos/plugins/*_TI_$(EB_PLATFORM)*

#TBD: Move not working if there are no folders to backup - find an alternative
move_plugins:
#	$(ECHO) Moving existing TI Plugins from EB Tresos plugins folder to $(EB_BACKUP) ...
#	$(MKDIR) $(EB_BACKUP)
#	$(MOVE) $(EB_PATH)/tresos/plugins/*_TI_$(EB_PLATFORM) $(EB_BACKUP)

moveback_plugins:
#	$(ECHO) Moving back existing TI Plugins from $(EB_BACKUP) to EB Tresos plugins folder ...
#	$(MOVE) $(EB_BACKUP)/*_TI_$(EB_PLATFORM) $(EB_PATH)/tresos/plugins
#	$(RMDIR) $(EB_BACKUP)

make_dir: rm_dir
	$(MKDIR) $(EB_WORKSPACE)

rm_dir:
	$(RMDIR) $(EB_OUTPUT_PATH)/include $(EB_OUTPUT_PATH)/src $(EB_OUTPUT_PATH)/swcd $(EB_EXTRA_OUTPUT_PATH)/include $(EB_EXTRA_OUTPUT_PATH)/src $(EB_EXTRA_OUTPUT_PATH)/swcd
	$(RMDIR) $(EB_WORKSPACE)

import_project: make_dir
	$(ECHO) Importing $(EB_PROJECT_NAME) ...
	$(EB_PATH_SCRIPT) -data $(EB_WORKSPACE) importProject $(EB_PROJECT_PATH)

generate_project: import_project
	$(ECHO) Generating $(EB_PROJECT_NAME) ...
	$(EB_PATH_SCRIPT) -data $(EB_WORKSPACE) -Dinfo=false generate $(EB_PROJECT_NAME)

delete_project:
	$(ECHO) Deleting $(EB_PROJECT_NAME) ...
	$(RMDIR) $(EB_WORKSPACE)
	$(RM) $(EB_PROJECT_PATH)/*/*.tdb $(EB_PROJECT_PATH)/*.tdb
