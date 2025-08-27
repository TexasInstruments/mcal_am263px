CAN_PATH=$(mcal_PATH)/Can

SRCDIR += $(CAN_PATH)/src
INCDIR += $(CAN_PATH)/include $(SRCDIR)
SRCS_COMMON += Can.c Can_Priv.c Can_Irq.c mcan.c Can_Mcan.c

# SOC specific files
SRCDIR += $(CAN_PATH)/V0
