UTILS_PATH=$(mcal_PATH)/examples/Utils

SRCDIR += $(UTILS_PATH)/$(COMPILER) $(UTILS_PATH)/$(COMPILER)/$(SOC)
SRCS_ASM_COMMON += sys_intvecs.asm sys_startup.asm
