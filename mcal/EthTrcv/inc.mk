ETHTRCV_PATH=$(mcal_PATH)/EthTrcv

INCDIR += $(ETHTRCV_PATH)/include

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  INCDIR += $(ETHTRCV_PATH)/V0
endif
ifeq ($(SOC), $(filter $(SOC), am273))
  INCDIR += $(ETHTRCV_PATH)/V1
endif
