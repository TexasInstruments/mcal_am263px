UTILS_PATH=$(mcal_PATH)/examples/Utils

include $(mcal_PATH)/Mcal_Lib/srcs.mk
SRCDIR += $(UTILS_PATH) $(UTILS_PATH)/$(SOC) $(UTILS_PATH)/$(COMPILER) $(UTILS_PATH)/$(COMPILER)/$(SOC)
INCDIR += $(UTILS_PATH) $(UTILS_PATH)/$(SOC) $(UTILS_PATH)/$(COMPILER) $(UTILS_PATH)/$(COMPILER)/$(SOC)
SRCS_COMMON += app_utils.c app_utils_uart.c sci.c trace.c
SRCS_COMMON += esm.c sys_vim.c Os.c CacheP.c
SRCS_COMMON += boot_armv7r.c MpuP_armv7r.c
SRCS_ASM_COMMON += sys_core.asm boot_armv7r_asm.asm MpuP_armv7r_asm.asm
