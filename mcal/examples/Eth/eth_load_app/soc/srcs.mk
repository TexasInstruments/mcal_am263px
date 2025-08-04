#App SOC files
SRCDIR += soc/$(SOC)/$(CORE) soc/$(SOC)/syscfg
INCDIR += soc/$(SOC)/$(CORE) soc/$(SOC)/syscfg
SRCS_COMMON += EthApp_Startup.c
SRCS_COMMON += ti_board_config.c ti_board_open_close.c ti_dpl_config.c ti_drivers_config.c
SRCS_COMMON += ti_drivers_open_close.c ti_pinmux_config.c ti_power_clock_config.c
