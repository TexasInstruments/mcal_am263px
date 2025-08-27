UTILS_PATH=$(mcal_PATH)/examples/Utils

SRCDIR += $(UTILS_PATH)
INCDIR += $(UTILS_PATH)/$(SOC) $(mcal_PATH)/autosar_include
SRCS_COMMON += Dem.c Det.c
