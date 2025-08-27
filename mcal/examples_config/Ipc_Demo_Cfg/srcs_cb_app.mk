IPC_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Ipc_Demo_Cfg

SRCDIR += $(IPC_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(IPC_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Cdd_Ipc_Callback_app_PBCfg.c
