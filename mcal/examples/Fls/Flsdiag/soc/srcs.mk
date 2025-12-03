#App SOC files
SRCDIR += soc/$(SOC)/$(CORE)
INCDIR += soc/$(SOC)/$(CORE)
SRCS_COMMON += Fls_Startup.c

SRCDIR += soc/$(SOC)/tresos/output/src
INCDIR += soc/$(SOC)/tresos/output/include
SRCS_COMMON += Fls_Cfg.c