MCU_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Mcu_Demo_Cfg

SRCDIR += $(MCU_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(MCU_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += Mcu_Cfg.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCS_COMMON += Mcu_PBcfg.c
endif
