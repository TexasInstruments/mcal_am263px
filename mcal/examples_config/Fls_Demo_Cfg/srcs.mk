FLS_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/Fls_Demo_Cfg

ifeq ($(SOC), $(filter $(SOC), am263px))
  ifeq ($(PACKAGE), SIP)
    SRCDIR += $(FLS_DEMO_CFG_PATH)/soc/$(SOC)_sip/r5f0_0/src
    INCDIR += $(FLS_DEMO_CFG_PATH)/soc/$(SOC)_sip/r5f0_0/include
  else
    SRCDIR += $(FLS_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
    INCDIR += $(FLS_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
  endif
else
  SRCDIR += $(FLS_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
  INCDIR += $(FLS_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
endif
SRCS_COMMON += Fls_Cfg.c Fls_PBcfg.c
