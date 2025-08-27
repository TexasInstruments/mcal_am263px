ETH_PATH=$(mcal_PATH)/Eth

SRCDIR += $(ETH_PATH)/src $(ETH_PATH)/src/cpsw
INCDIR += $(ETH_PATH)/include $(ETH_PATH)/src/cpsw/include $(ETH_PATH)/src/hw
SRCS_COMMON += Eth.c Eth_Irq.c
SRCS_COMMON += Eth_Priv.c Eth_Helpers.c Cpsw.c Cpsw_Ale.c Cpsw_Mdio.c Cpsw_Stats.c Cpsw_Cpts.c Cpsw_Port.c Cpsw_Cpdma.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(ETH_PATH)/V0
  INCDIR += $(ETH_PATH)/V0
endif
