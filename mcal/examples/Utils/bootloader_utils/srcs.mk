BOOTLOADER_UTILS_PATH=$(mcal_PATH)/examples/Utils/bootloader_utils
include $(mcal_PATH)/examples/Utils/inc.mk
include $(mcal_PATH)/Fls/inc.mk

SRCDIR += $(BOOTLOADER_UTILS_PATH)
INCDIR += $(BOOTLOADER_UTILS_PATH)
SRCS_COMMON += bootloader.c bootloader_fls.c

#SOC files
ifeq ($(SOC), $(filter $(SOC), am263px))
  SRCDIR += $(BOOTLOADER_UTILS_PATH)/$(SOC)
  INCDIR += $(BOOTLOADER_UTILS_PATH)/$(SOC)
  SRCS_COMMON += soc_rcm.c soc.c bootloader_soc.c
endif
