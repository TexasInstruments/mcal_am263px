#App SOC files
SRCDIR += soc/$(SOC)/$(CORE)
INCDIR += soc/$(SOC)/$(CORE)
SRCS_COMMON += FlsApp_Startup.c

#App config files
SRCDIR += soc/$(SOC)/tresos/output/src
INCDIR += soc/$(SOC)/tresos/output/include
SRCS_COMMON += Fls_Cfg.c Fls_PBcfg.c Cdd_Dma_Cfg.c
