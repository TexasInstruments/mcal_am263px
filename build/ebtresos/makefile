export MCAL_PATH := $(abspath ../../)
include $(MCAL_PATH)/build/imports.mk

EB_MAKE_PATH=$(MCAL_PATH)/build/ebtresos
EB_MAKE_FILE=makefile.mk

.PHONY: all copy_plugins delete_plugins AM263x_targets AM263Px_targets AM261x_targets

all: move_plugins copy_plugins $(EB_PLATFORM)_targets delete_plugins moveback_plugins
ifeq ($(PLATFORM),$(filter $(PLATFORM), am263px))
	$(MAKE) AM263Px_C_targets
	$(MAKE) AM263Px_SIP_targets
endif

move_plugins:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) move_plugins   	EB_PLATFORM=$(EB_PLATFORM)

copy_plugins:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) copy_plugins   	EB_PLATFORM=$(EB_PLATFORM)

delete_plugins:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) delete_plugins 	EB_PLATFORM=$(EB_PLATFORM)

moveback_plugins:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) moveback_plugins 	EB_PLATFORM=$(EB_PLATFORM)

AM263x_targets:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Mcal_Demo_Cfg          EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Mcal_Demo_Cfg/soc/am263/tresos       EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Mcal_Demo_Cfg/soc/am263/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_app                EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am263/tresos                EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am263/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_intr_app           EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am263/tresos           EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am263/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_multichannel_app	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am263/tresos   EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am263/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=wdg_skip_reset_app  	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am263/tresos     EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am263/tresos/output

AM263Px_targets:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Mcal_Demo_Cfg          EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Mcal_Demo_Cfg/soc/am263px/tresos     EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Mcal_Demo_Cfg/soc/am263px/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Fls_OSPI_SBL_Support_Cfg  	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Fls_OSPI_SBL_Support_Cfg/soc/am263px/tresos   EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Fls_OSPI_SBL_Support_Cfg/soc/am263px/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=adc_hw_trig_dma_app 	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_hw_trig_dma_app/soc/am263px/tresos  EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_hw_trig_dma_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=adc_resolver_app    	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_resolver_app/soc/am263px/tresos     EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_resolver_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=adc_resolver_dma_app   EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_resolver_dma_app/soc/am263px/tresos EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_resolver_dma_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=fls_boot_app           EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Bootloader/fls_boot_app/soc/am263px/tresos  EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Bootloader/fls_boot_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_app                EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am263px/tresos              EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_intr_app           EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am263px/tresos         EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_multichannel_app	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am263px/tresos EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=wdg_skip_reset_app  	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am263px/tresos   EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am263px/tresos/output

AM263Px_C_targets:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) copy_plugins   EB_PLATFORM=$(EB_PLATFORM) PACKAGE=C
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all            EB_PLATFORM=$(EB_PLATFORM) PACKAGE=C   EB_PROJECT_NAME=can_app_lp  EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Can/soc/am263px/tresos/am263px_lp  EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Can/soc/am263px/tresos/am263px_lp/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) delete_plugins EB_PLATFORM=$(EB_PLATFORM) PACKAGE=C

AM263Px_SIP_targets:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) copy_plugins   EB_PLATFORM=$(EB_PLATFORM) PACKAGE=SIP
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all            EB_PLATFORM=$(EB_PLATFORM) PACKAGE=SIP EB_PROJECT_NAME=can_app_sip EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Can/soc/am263px/tresos/am263px_sip EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Can/soc/am263px/tresos/am263px_sip/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) delete_plugins EB_PLATFORM=$(EB_PLATFORM) PACKAGE=SIP

AM261x_targets:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Mcal_Demo_Cfg          EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Mcal_Demo_Cfg/soc/am261/tresos       EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Mcal_Demo_Cfg/soc/am261/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Fls_OSPI_SBL_Support_Cfg  	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Fls_OSPI_SBL_Support_Cfg/soc/am261/tresos   EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Fls_OSPI_SBL_Support_Cfg/soc/am261/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_app                EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am261/tresos                EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am261/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_intr_app           EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am261/tresos           EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am261/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_multichannel_app	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am261/tresos   EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am261/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=wdg_skip_reset_app  	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am261/tresos     EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am261/tresos/output
