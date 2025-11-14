include $(mcal_PATH)/Ipc/inc.mk

SRCDIR += $(mcal_PATH)/Ipc/src
SRCS_COMMON += Cdd_Ipc.c Cdd_Ipc_Irq.c ipc_notify_v1_cfg_lld.c ipc_notify_v1_lld.c
SRCS_COMMON += ipc_rpmsg_lld_vring.c ipc_rpmsg_lld.c ipc_notify_lld_utils.c
# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px))
  SRCDIR += $(mcal_PATH)/Ipc/V0
endif
ifeq ($(SOC), $(filter $(SOC), am261))
  SRCDIR += $(mcal_PATH)/Ipc/V2
endif
