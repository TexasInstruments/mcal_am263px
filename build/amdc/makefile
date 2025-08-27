export MCAL_PATH := $(abspath ../../)
include $(MCAL_PATH)/build/imports.mk

MCAL_PLUGIN_PATH=$(MCAL_PATH)/mcal_config/plugins/$(EB_PLATFORM)
AMDC_PATH=$(MCAL_PATH)/mcal_misc/MCAL_Automation/Vector_AMDC_1.1/AMDC

# List of standard MCAL modules separate by space
MODULE_LIST_AMDC=Adc Can Cdd_Dma Cdd_FsiRx Cdd_FsiTx Cdd_I2c Cdd_Ipc Cdd_Pwm Cdd_Uart Dio Eth EthTrcv Fls Gpt Icu Lin Mcu Pwm Spi Wdg

TARGET_MODULE_LIST_AMDC=$(addsuffix _amdc, $(MODULE_LIST_AMDC))

# Output directory where the generated log is stored.
# The log files are checked-in as we have false positive with this tool and any new violation can be easily checked and approved.
AMDC_LOG_DIR=output/$(EB_PLATFORM)

.PHONY : all clean amdc_check $(TARGET_MODULE_LIST_AMDC) special_targets_AM263x special_targets_AM263Px special_targets_AM261x

all: clean
	$(MKDIR) $(AMDC_LOG_DIR)
	$(MAKE) amdc_check

clean:
	$(RMDIR) $(AMDC_LOG_DIR)

amdc_check: $(TARGET_MODULE_LIST_AMDC) special_targets_$(EB_PLATFORM)

$(TARGET_MODULE_LIST_AMDC):
	$(ECHO) AMDC Check for $(subst _amdc,,$@) ...
	$(AMDC_PATH) -s $(MCAL_PLUGIN_PATH)/$(subst _amdc,,$@)_TI_$(EB_PLATFORM)/config/$(subst _amdc,,$@).arxml -o $(AMDC_LOG_DIR)
	$(ECHO) AMDC Check for $(subst _amdc,,$@) Completed!!!

special_targets_AM263x:
	$(ECHO) AMDC Check for AM263x Port ...
	$(AMDC_PATH) -s $(MCAL_PLUGIN_PATH)/Port_TI_AM263x/config/Port_AM263x.arxml -o $(AMDC_LOG_DIR)

special_targets_AM263Px:
	$(ECHO) AMDC Check for AM263Px_C EthTrcv ...
	$(AMDC_PATH) -s $(MCAL_PLUGIN_PATH)/EthTrcv_TI_AM263Px_C/config/EthTrcv_C.arxml -o $(AMDC_LOG_DIR)
	$(ECHO) AMDC Check for AM263Px_C Port ...
	$(AMDC_PATH) -s $(MCAL_PLUGIN_PATH)/Port_TI_AM263Px_C/config/Port_AM263Px_C.arxml -o $(AMDC_LOG_DIR)
	$(ECHO) AMDC Check for AM263Px_SIP Port ...
	$(AMDC_PATH) -s $(MCAL_PLUGIN_PATH)/Port_TI_AM263Px_SIP/config/Port_AM263Px_SIP.arxml -o $(AMDC_LOG_DIR)

special_targets_AM261x:
	$(ECHO) AMDC Check for AM261x_ZCZ Port ...
	$(AMDC_PATH) -s $(MCAL_PLUGIN_PATH)/Port_TI_AM261x_ZCZ/config/Port_AM261x.arxml -o $(AMDC_LOG_DIR)
