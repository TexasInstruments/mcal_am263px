ETH_PATH=$(mcal_PATH)/Eth

INCDIR += $(ETH_PATH)/include $(ETH_PATH)/src/cpsw/include $(ETH_PATH)/src/hw

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  INCDIR += $(ETH_PATH)/V0
endif
ifeq ($(SOC), $(filter $(SOC), am273))
  INCDIR += $(ETH_PATH)/V1
endif
