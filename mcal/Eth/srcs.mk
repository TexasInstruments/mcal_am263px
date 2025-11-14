include $(mcal_PATH)/Eth/inc.mk

SRCDIR += $(mcal_PATH)/Eth/src $(mcal_PATH)/Eth/src/cpsw
SRCS_COMMON += Eth.c Eth_Irq.c
SRCS_COMMON += Eth_Priv.c Eth_Helpers.c Cpsw.c Cpsw_Ale.c Cpsw_Mdio.c Cpsw_Stats.c Cpsw_Cpts.c Cpsw_Port.c Cpsw_Cpdma.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Eth/V0
