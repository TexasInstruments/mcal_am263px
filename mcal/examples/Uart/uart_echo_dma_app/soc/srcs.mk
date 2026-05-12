#App SOC files
SRCDIR += soc/$(SOC)/$(CORE)
INCDIR += soc/$(SOC)/$(CORE)
SRCS_COMMON += UartEchoDma_Startup.c

#App config files (AM261: own tresos output in DMA mode)
ifeq ($(SOC), am261)
SRCDIR += soc/$(SOC)/tresos/output/src
INCDIR += soc/$(SOC)/tresos/output/include
SRCS_COMMON += Cdd_Uart_Cfg.c Cdd_Uart_PBcfg.c
endif
