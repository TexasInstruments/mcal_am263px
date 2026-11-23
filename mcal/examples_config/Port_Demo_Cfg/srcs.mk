PORT_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Port_Demo_Cfg

PORT_CFG_BASE=$(PORT_DEMO_CFG_PATH)/soc/$(SOC)/$(CORE)
ifeq ($(SOC)/$(PACKAGE),am261/ZNC)
  PORT_CFG_BASE=$(PORT_DEMO_CFG_PATH)/soc/am261/tresos_znc/output
endif

SRCDIR += $(PORT_CFG_BASE)/src
INCDIR += $(PORT_CFG_BASE)/include
SRCS_COMMON += Port_Cfg.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263))
  SRCS_COMMON += Port_PBcfg.c
endif
ifeq ($(SOC), $(filter $(SOC), am263px))
  ifeq ($(PACKAGE), SIP)
    SRCS_COMMON += Port_PBcfg_SIP.c
  else
    ifeq ($(PACKAGE), C)
      SRCS_COMMON += Port_PBcfg_C.c
    else
      SRCS_COMMON += Port_PBcfg.c
    endif
  endif
endif
ifeq ($(SOC), $(filter $(SOC), am261))
  SRCS_COMMON += Port_PBcfg.c
endif
