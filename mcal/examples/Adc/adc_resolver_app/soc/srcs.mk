#App SOC files
SRCDIR += soc/$(SOC)/$(CORE)
INCDIR += soc
SRCS_COMMON += AdcApp_Platform.c

#App config files
SRCDIR += soc/$(SOC)/tresos/output/src
INCDIR += soc/$(SOC)/tresos/output/include
SRCS_COMMON += Adc_Cfg.c Adc_PBcfg.c Cdd_I2c_Cfg.c Mcu_Cfg.c Mcu_PBcfg.c
