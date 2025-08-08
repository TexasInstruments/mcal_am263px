PORT_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Port_Demo_Cfg

SRCDIR += $(PORT_DEMO_CFG_PATH)/soc/$(SOC)/$(CORE)/src
INCDIR += $(PORT_DEMO_CFG_PATH)/soc/$(SOC)/$(CORE)/include
SRCS_COMMON += Port_Cfg.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263))
  SRCS_COMMON += Port_PBcfg_UART0.c
endif
ifeq ($(SOC), $(filter $(SOC), am263px))
  ifeq ($(PACKAGE), SIP)
    SRCS_COMMON += Port_PBcfg_UART0.c
  else
    ifeq ($(PACKAGE), C)
      SRCS_COMMON += Port_PBcfg_UART0.c
    else
      SRCS_COMMON += Port_PBcfg_UART0.c
    endif
  endif
endif
ifeq ($(SOC), $(filter $(SOC), am261))
  SRCS_COMMON += Port_PBcfg_UART0.c
endif
