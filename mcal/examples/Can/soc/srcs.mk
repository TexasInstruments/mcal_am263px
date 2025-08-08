#App SOC files
SRCDIR += soc/$(SOC)/$(CORE)
INCDIR += soc/$(SOC)/$(CORE)
SRCS_COMMON += CanApp_Startup.c

#App config files
ifeq ($(SOC), $(filter $(SOC), am263 am261))
  include $(mcal_PATH)/examples_config/Port_Demo_Cfg/srcs.mk
endif
ifeq ($(SOC), $(filter $(SOC), am263px))
  ifeq ($(PACKAGE), SIP)
    SRCDIR += soc/$(SOC)/tresos/am263px_sip/output/src
    INCDIR += soc/$(SOC)/tresos/am263px_sip/output/include
    SRCS_COMMON += Port_Cfg.c Port_PBcfg.c
  else
    ifeq ($(PACKAGE), C)
      SRCDIR += soc/$(SOC)/tresos/am263px_lp/output/src
      INCDIR += soc/$(SOC)/tresos/am263px_lp/output/include
      SRCS_COMMON += Port_Cfg.c Port_PBcfg.c
    else
      include $(mcal_PATH)/examples_config/Port_Demo_Cfg/srcs.mk
    endif
  endif
endif
