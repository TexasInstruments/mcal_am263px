FSS_UTILS_PATH=$(mcal_PATH)/examples/Utils/fss_utils
HSMCLIENT_UTILS_PATH=$(mcal_PATH)/examples/Utils/hsmclient_utils
include $(mcal_PATH)/examples/Utils/inc.mk

SRCDIR += $(FSS_UTILS_PATH)
INCDIR += $(FSS_UTILS_PATH)

INCDIR += $(HSMCLIENT_UTILS_PATH)/dpl/

SRCS_COMMON += fss_v0.c
