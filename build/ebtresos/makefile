export MCAL_PATH := $(abspath ../../)

#Default platform
export PLATFORM?=am263px
include $(MCAL_PATH)/build/imports.mk

EB_MAKE_PATH=$(MCAL_PATH)/build/ebtresos
EB_MAKE_FILE=makefile.mk

.PHONY: all copy_plugins delete_plugins AM263x_targets AM263Px_targets AM261x_targets

all: move_plugins copy_plugins $(EB_PLATFORM)_targets delete_plugins moveback_plugins

move_plugins:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) move_plugins   	EB_PLATFORM=$(EB_PLATFORM)

copy_plugins:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) copy_plugins   	EB_PLATFORM=$(EB_PLATFORM)

delete_plugins:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) delete_plugins 	EB_PLATFORM=$(EB_PLATFORM)

moveback_plugins:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) moveback_plugins 	EB_PLATFORM=$(EB_PLATFORM)

AM263x_targets:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_app                EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am263/tresos                EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am263/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_intr_app           EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am263/tresos           EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am263/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_multichannel_app	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am263/tresos   EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am263/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=wdg_skip_reset_app  	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am263/tresos     EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am263/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Dio_Demo_Cfg        	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Dio_Demo_Cfg/soc/am263/tresos        EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Dio_Demo_Cfg/soc/am263/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Cdd_I2c_Demo_Cfg       EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Cdd_I2c_Demo_Cfg/soc/am263/tresos    EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Cdd_I2c_Demo_Cfg/soc/am263/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Wdg_Demo_Cfg        	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Wdg_Demo_Cfg/soc/am263/tresos        EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Wdg_Demo_Cfg/soc/am263/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Lin_Demo_Cfg           EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Lin_Demo_Cfg/soc/am263/tresos        EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Lin_Demo_Cfg/soc/am263/r5f0_0

AM263Px_targets:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=adc_hw_trig_dma_app 	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_hw_trig_dma_app/soc/am263px/tresos  EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_hw_trig_dma_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=adc_resolver_app    	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_resolver_app/soc/am263px/tresos     EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_resolver_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=adc_resolver_dma_app   EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_resolver_dma_app/soc/am263px/tresos EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Adc/adc_resolver_dma_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=can_app             	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Can/soc/am263px/tresos                      EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Can/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=can_app_lp          	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Can/soc/am263px/tresos_lp                   EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Can/soc/am263px/tresos_lp/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=fls_app             	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Fls/soc/am263px/tresos                      EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Fls/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=fls_app_lp          	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Fls/soc/am263px/tresos_lp                   EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Fls/soc/am263px/tresos_lp/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_app                EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am263px/tresos              EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_intr_app           EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am263px/tresos         EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_multichannel_app	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am263px/tresos EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=wdg_skip_reset_app  	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am263px/tresos   EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am263px/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Dio_Demo_Cfg        	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Dio_Demo_Cfg/soc/am263px/tresos      EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Dio_Demo_Cfg/soc/am263px/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Cdd_I2c_Demo_Cfg       EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Cdd_I2c_Demo_Cfg/soc/am263px/tresos  EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Cdd_I2c_Demo_Cfg/soc/am263px/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Cdd_I2c_Demo_Cfg_Lp  	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Cdd_I2c_Demo_Cfg/soc/am263px_lp/tresos EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Cdd_I2c_Demo_Cfg/soc/am263px_lp/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Wdg_Demo_Cfg        	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Wdg_Demo_Cfg/soc/am263px/tresos      EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Wdg_Demo_Cfg/soc/am263px/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Lin_Demo_Cfg           EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Lin_Demo_Cfg/soc/am263px/tresos      EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Lin_Demo_Cfg/soc/am263px/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Dma_Demo_Cfg           EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Dma_Demo_Cfg/soc/am263px/tresos      EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Dma_Demo_Cfg/soc/am263px/r5f0_0

AM261x_targets:
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_app                EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am261/tresos                EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_app/soc/am261/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_intr_app           EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am261/tresos           EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_intr_app/soc/am261/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=i2c_multichannel_app	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am261/tresos   EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/I2c/i2c_multichannel_app/soc/am261/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=wdg_skip_reset_app  	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am261/tresos     EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples/Wdg/wdg_skip_reset_app/soc/am261/tresos/output
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Dio_Demo_Cfg        	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Dio_Demo_Cfg/soc/am261/tresos        EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Dio_Demo_Cfg/soc/am261/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Cdd_I2c_Demo_Cfg       EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Cdd_I2c_Demo_Cfg/soc/am261/tresos    EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Cdd_I2c_Demo_Cfg/soc/am261/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Wdg_Demo_Cfg        	EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Wdg_Demo_Cfg/soc/am261/tresos        EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Wdg_Demo_Cfg/soc/am261/r5f0_0
	$(MAKE) -C $(EB_MAKE_PATH) -f $(EB_MAKE_FILE) all EB_PLATFORM=$(EB_PLATFORM) EB_PROJECT_NAME=Lin_Demo_Cfg           EB_PROJECT_PATH=$(MCAL_PATH)/mcal/examples_config/Lin_Demo_Cfg/soc/am261/tresos        EB_OUTPUT_PATH=$(MCAL_PATH)/mcal/examples_config/Lin_Demo_Cfg/soc/am261/r5f0_0
