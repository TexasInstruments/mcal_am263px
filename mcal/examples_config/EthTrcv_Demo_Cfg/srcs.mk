ETHTRCV_DEMO_CFG_PATH=$(mcal_PATH)/examples_config/EthTrcv_Demo_Cfg

SRCDIR += $(ETHTRCV_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/src
INCDIR += $(ETHTRCV_DEMO_CFG_PATH)/soc/$(SOC)/r5f0_0/include
SRCS_COMMON += EthTrcv_Cfg.c EthTrcv_Lcfg.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263))
  SRCS_COMMON += EthTrcv_PBcfg.c
endif
ifeq ($(SOC), $(filter $(SOC), am263px))
  ifeq ($(PACKAGE), SIP)
    SRCS_COMMON += EthTrcv_PBcfg.c
  else
    ifeq ($(PACKAGE), C)
      SRCS_COMMON += EthTrcv_PBcfg_C.c
    else
      SRCS_COMMON += EthTrcv_PBcfg.c
    endif
  endif
endif
ifeq ($(SOC), $(filter $(SOC), am261))
  SRCS_COMMON += EthTrcv_PBcfg.c
endif
ifeq ($(SOC), $(filter $(SOC), am273 am2732s))
  SRCS_COMMON += EthTrcv_PBcfg.c
endif
