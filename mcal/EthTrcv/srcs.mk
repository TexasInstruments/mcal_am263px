include $(mcal_PATH)/EthTrcv/inc.mk

SRCDIR += $(mcal_PATH)/EthTrcv/src
SRCS_COMMON += EthTrcv.c EthTrcv_Priv.c
# SOC specific files
SRCDIR += $(mcal_PATH)/EthTrcv/V0
