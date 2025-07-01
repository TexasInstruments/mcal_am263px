LIN_PATH=$(mcal_PATH)/Lin

SRCDIR += $(LIN_PATH)/src
INCDIR += $(LIN_PATH)/include
SRCS_COMMON += Lin.c Lin_Priv.c Lin_Irq.c

# SOC specific files
SRCDIR += $(LIN_PATH)/V0
INCDIR += $(LIN_PATH)/V0
