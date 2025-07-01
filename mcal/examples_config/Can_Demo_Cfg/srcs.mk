CAN_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Can_Demo_Cfg

SRCDIR += $(CAN_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(CAN_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Can_Cfg.c Can_PBcfg.c
