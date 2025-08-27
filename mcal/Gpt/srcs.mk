GPT_PATH=$(mcal_PATH)/Gpt

SRCDIR += $(GPT_PATH)/src
INCDIR += $(GPT_PATH)/include
SRCS_COMMON += Gpt.c Gpt_Irq.c Gpt_Priv.c

# SOC specific files
SRCDIR += $(GPT_PATH)/V0
INCDIR += $(GPT_PATH)/V0
