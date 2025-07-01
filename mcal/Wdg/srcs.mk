WDG_PATH=$(mcal_PATH)/Wdg

SRCDIR += $(WDG_PATH)/src
INCDIR += $(WDG_PATH)/include
SRCS_COMMON += Wdg.c Wdg_Priv.c

# SOC specific files
SRCDIR += $(WDG_PATH)/V0
INCDIR += $(WDG_PATH)/V0
