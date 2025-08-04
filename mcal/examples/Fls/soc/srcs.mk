#App SOC files
SRCDIR += soc/$(SOC)/$(CORE)
INCDIR += soc/$(SOC)/$(CORE)
SRCS_COMMON += FlsApp_Startup.c

ifeq ($(SOC), am263px)
  SRCS_COMMON += Cdd_I2c_Cfg.c
  ifeq ($(PACKAGE), SIP)
    SRCDIR += soc/$(SOC)/tresos/output/src
    INCDIR += soc/$(SOC)/tresos/output/include
  else
    ifeq ($(PACKAGE), C)
      SRCDIR += soc/$(SOC)/tresos_lp/output/src
      INCDIR += soc/$(SOC)/tresos_lp/output/include
    else
      SRCDIR += soc/$(SOC)/tresos/output/src
      INCDIR += soc/$(SOC)/tresos/output/include
    endif
  endif
endif
