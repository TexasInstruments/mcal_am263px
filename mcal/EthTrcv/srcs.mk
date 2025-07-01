ETHTRCV_PATH=$(mcal_PATH)/EthTrcv

SRCDIR += $(ETHTRCV_PATH)/src
INCDIR += $(ETHTRCV_PATH)/include
SRCS_COMMON += EthTrcv.c EthTrcv_Priv.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(ETHTRCV_PATH)/V0
  INCDIR += $(ETHTRCV_PATH)/V0
endif
ifeq ($(SOC), $(filter $(SOC), am273))
  SRCDIR += $(ETHTRCV_PATH)/V1
  INCDIR += $(ETHTRCV_PATH)/V1
endif
