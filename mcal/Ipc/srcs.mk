IPC_PATH=$(mcal_PATH)/Ipc

SRCDIR += $(IPC_PATH)/src
INCDIR += $(IPC_PATH)/include
SRCS_COMMON += Cdd_Ipc.c Cdd_Ipc_Irq.c ipc_notify_v1_cfg_lld.c ipc_notify_v1_lld.c
SRCS_COMMON += ipc_rpmsg_lld_vring.c ipc_rpmsg_lld.c ipc_notify_lld_utils.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px))
  SRCDIR += $(IPC_PATH)/V0
  INCDIR += $(IPC_PATH)/V0
endif
ifeq ($(SOC), $(filter $(SOC), am273))
  SRCDIR += $(IPC_PATH)/V1
  INCDIR += $(IPC_PATH)/V1
endif
ifeq ($(SOC), $(filter $(SOC), am261))
  SRCDIR += $(IPC_PATH)/V2
  INCDIR += $(IPC_PATH)/V2
endif
