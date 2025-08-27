UART_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Uart_Demo_Cfg

SRCDIR += $(UART_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(UART_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Cdd_Uart_Cfg.c Cdd_Uart_PBcfg.c
