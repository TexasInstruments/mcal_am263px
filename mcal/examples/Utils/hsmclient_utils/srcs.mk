HSMCLIENT_UTILS_PATH=$(mcal_PATH)/examples/Utils/hsmclient_utils
include $(mcal_PATH)/examples/Utils/inc.mk
include $(mcal_PATH)/examples/Utils/inc_autosar_stub.mk

INCDIR += $(BOOTLOADER_UTILS_PATH)/$(SOC)

# DPL files - TODO remove this after migrating to MCAL utils
SRCDIR += $(HSMCLIENT_UTILS_PATH)/dpl/
INCDIR += $(HSMCLIENT_UTILS_PATH)/dpl/
SRCS_S_COMMON += HwiP_armv7r_asm.S
SRCS_COMMON += CpuId_armv7r.c SemaphoreP_nortos.c

# Secure IPC files
SRCDIR += $(HSMCLIENT_UTILS_PATH)/secure_ipc_notify
INCDIR += $(HSMCLIENT_UTILS_PATH)/secure_ipc_notify
INCDIR += $(HSMCLIENT_UTILS_PATH)/secure_ipc_notify/soc/
SRCS_COMMON += sipc_notify_src.c
# Secure IPC SOC files
SRCDIR += $(HSMCLIENT_UTILS_PATH)/secure_ipc_notify/soc/$(SOC)
INCDIR += $(HSMCLIENT_UTILS_PATH)/secure_ipc_notify/soc/$(SOC)
SRCS_COMMON += sipc_notify_cfg.c

# HSM Utils files
SRCDIR += $(HSMCLIENT_UTILS_PATH)
SRCDIR += $(HSMCLIENT_UTILS_PATH)/hsmclient
SRCDIR += $(HSMCLIENT_UTILS_PATH)/hsmclient/utils
INCDIR += $(HSMCLIENT_UTILS_PATH)
INCDIR += $(HSMCLIENT_UTILS_PATH)/hsmclient
INCDIR += $(HSMCLIENT_UTILS_PATH)/hsmclient/utils
SRCS_COMMON += hsmclient.c
SRCS_COMMON += hsmclient_utils.c

# Crypto Utils files
SRCDIR += $(HSMCLIENT_UTILS_PATH)/crypto/dthe
INCDIR += $(HSMCLIENT_UTILS_PATH)/crypto/dthe
INCDIR += $(HSMCLIENT_UTILS_PATH)/crypto/dthe/hw_include
SRCS_COMMON += dma.c dthe.c dthe_aes.c dthe_sha.c
