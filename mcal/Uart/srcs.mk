UART_PATH=$(mcal_PATH)/Uart

SRCDIR += $(UART_PATH)/src
INCDIR += $(UART_PATH)/include
SRCS_COMMON += Cdd_Uart.c Cdd_Uart_Irq.c
SRCS_COMMON += Cdd_Uart_Priv.c uart.c uart_dma_edma.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(UART_PATH)/V0
  INCDIR += $(UART_PATH)/V0
endif
