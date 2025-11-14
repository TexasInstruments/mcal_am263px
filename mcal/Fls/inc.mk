INCDIR += $(mcal_PATH)/Fls/include
# For CacheP APIs
INCDIR += $(mcal_PATH)/examples/Utils/CLANG/$(SOC)
# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263))
  INCDIR += $(mcal_PATH)/Fls/V0
endif
ifeq ($(SOC), $(filter $(SOC), am263px am261))
  INCDIR += $(mcal_PATH)/Fls/V2
endif
