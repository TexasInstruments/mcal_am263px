include $(mcal_PATH)/Uart/inc.mk

SRCDIR += $(mcal_PATH)/Uart/src
SRCS_COMMON += Cdd_Uart.c Cdd_Uart_Irq.c
SRCS_COMMON += Cdd_Uart_Priv.c uart.c uart_dma_edma.c
# SOC specific files
SRCDIR += $(mcal_PATH)/Uart/V0
