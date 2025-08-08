PORT_PATH=$(mcal_PATH)/Port

SRCDIR += $(PORT_PATH)/src
INCDIR += $(PORT_PATH)/include
SRCS_COMMON += Port.c Port_Priv.c Port_Irq.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(PORT_PATH)/V0
  INCDIR += $(PORT_PATH)/V0
endif
