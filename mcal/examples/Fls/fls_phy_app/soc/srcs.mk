#App SOC files
SRCDIR += soc/$(SOC)/$(CORE)
INCDIR += soc/$(SOC)/$(CORE)
SRCS_COMMON += FlsApp_Startup.c

ifeq ($(SOC), $(filter $(SOC), am263px))
  ifeq ($(PACKAGE), SIP)
    SRCDIR += soc/$(SOC)/tresos_sip/output/src
    INCDIR += soc/$(SOC)/tresos_sip/output/include
  else
    SRCDIR += soc/$(SOC)/tresos/output/src
    INCDIR += soc/$(SOC)/tresos/output/include
  endif
else
  SRCDIR += soc/$(SOC)/tresos/output/src
  INCDIR += soc/$(SOC)/tresos/output/include
endif
SRCS_COMMON += Fls_Cfg.c