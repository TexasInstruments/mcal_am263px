include $(mcal_PATH)/Gpt/inc.mk

SRCDIR += $(mcal_PATH)/Gpt/src
SRCS_COMMON += Gpt.c Gpt_Irq.c Gpt_Priv.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Gpt/V0
