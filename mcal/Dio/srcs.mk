include $(mcal_PATH)/Dio/inc.mk

SRCDIR += $(mcal_PATH)/Dio/src
SRCS_COMMON += Dio.c Dio_Priv.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Dio/V0
