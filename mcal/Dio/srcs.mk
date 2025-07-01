DIO_PATH=$(mcal_PATH)/Dio

SRCDIR += $(DIO_PATH)/src
INCDIR += $(DIO_PATH)/include
SRCS_COMMON += Dio.c Dio_Priv.c

# SOC specific files
ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
  SRCDIR += $(DIO_PATH)/V0
  INCDIR += $(DIO_PATH)/V0
endif
ifeq ($(SOC), $(filter $(SOC), am273))
  SRCDIR += $(DIO_PATH)/V1
  INCDIR += $(DIO_PATH)/V1
endif
