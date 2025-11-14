#*******************************************************************************
#                                                                              *
# Copyright (c) 2023 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# File: mcal_component.mk
#       This file is component include make file of MCAL.
# List of variables set in this file and their purpose:
# <mod>_RELPATH        - This is the relative path of the module, typically from
#                        top-level directory of the package
# <mod>_PATH           - This is the absolute path of the module. It derives from
#                        absolute path of the top-level directory (set in env.mk)
#                        and relative path set above
# <mod>_INCLUDE        - This is the path that has interface header files of the
#                        module. This can be multiple directories (space separated)
# <mod>_PKG_LIST       - Names of the modules (and sub-modules) that are a part
#                        part of this module, including itself.
# <mod>_PLATFORM_DEPENDENCY - "yes": means the code for this module depends on
#                             platform and the compiled obj/lib has to be kept
#                             under <platform> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no platform dependent code and hence
#                             the obj/libs are not kept under <platform> dir.
# <mod>_CORE_DEPENDENCY     - "yes": means the code for this module depends on
#                             core and the compiled obj/lib has to be kept
#                             under <core> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no core dependent code and hence
#                             the obj/libs are not kept under <core> dir.
# <mod>_APP_STAGE_FILES     - List of source files that belongs to the module
#                             <mod>, but that needs to be compiled at application
#                             build stage (in the context of the app). This is
#                             primarily for link time configurations or if the
#                             source file is dependent on options/defines that are
#                             application dependent. This can be left blank or
#                             not defined at all, in which case, it means there
#                             no source files in the module <mod> that are required
#                             to be compiled in the application build stage.
#
ifeq ($(mcal_component_make_include), )

ifeq ($(PLATFORM),$(filter $(PLATFORM), am263))
DEFAULT_SOCLIST = am263
MCAL_SOC_FILES = V0
MCAL_MCU_SOC_FILES = V0
MCAL_FLS_SOC_FILES = V0
endif

ifeq ($(PLATFORM),$(filter $(PLATFORM), am263px))
DEFAULT_SOCLIST = am263px
MCAL_SOC_FILES = V0
MCAL_MCU_SOC_FILES = V2
MCAL_FLS_SOC_FILES = V2
endif

ifeq ($(PLATFORM),$(filter $(PLATFORM), am261))
DEFAULT_SOCLIST = am261
MCAL_SOC_FILES = V0
MCAL_MCU_SOC_FILES = V3
MCAL_FLS_SOC_FILES = V2
endif

############################
# device mcal package
# List of components included under mcal lib
# The components included here are built and will be part of mcal lib
# mcal HW files will be included in this order :
# 1. SOC specific HW file - $(mcal_PATH)/include/$(SOCFAMILY)/$(SOC)/hw
# 2. SOC Family specific HW file - $(mcal_PATH)/include/$(SOCFAMILY)/hw
# 3. Common HW file - $(mcal_PATH)/include/hw
############################

############################
# device mcal package
# List of components included under mcal lib
# The components included here are built and will be part of mcal lib
############################
mcal_mcal_LIB_LIST =

############################
# device mcal application utility packages
# List of application utilities under mcal
# The components included here are built and will be part of mcal app_lib
############################
mcal_mcal_APP_LIB_LIST =

############################
# device mcal examples
# List of examples under mcal
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
mcal_mcal_EXAMPLE_LIST =

############################
# device kw targets
# List of kw targets
# All the kw targets mentioned in list are built when allkw target is called
# List below all kw targtes for allowed values
############################
mcal_mcal_KW_LIST =

############################
# Duplicate example list which should not be built with "all" (since this is
# duplicate -j option will build both and result in .obj correuption) but needs
# to be still exposed to top level makefile so that user can individually call
# them. Also these duplicate targets doesn't support package option and hence
# should not be included when packaging
############################
mcal_mcal_DUP_EXAMPLE_LIST =

ifeq ($(PLATFORM),$(filter $(PLATFORM), am263))
mcal_mcal_LIB_LIST = mcu port gpt spi can cdd_cmpss wdg fls adc pwm icu ipc dma eth ethtrcv i2c uart fsitx fsirx lin epwm dio
endif

ifeq ($(PLATFORM),$(filter $(PLATFORM), am263px))
mcal_mcal_LIB_LIST = mcu port gpt spi can cdd_cmpss cdd_flc wdg adc pwm icu ipc dma eth ethtrcv i2c uart fsitx fsirx lin fls epwm dio bootloader_utils
endif

ifeq ($(PLATFORM),$(filter $(PLATFORM), am261))
mcal_mcal_LIB_LIST = mcu port gpt spi can cdd_cmpss cdd_flc wdg fls adc pwm icu ipc dma eth ethtrcv i2c uart dio lin epwm fsitx fsirx
endif

############################
# cdddma mcal lib
############################
dma_COMP_LIST = dma
dma_RELPATH = Dma
dma_PATH = $(mcal_PATH)/$(dma_RELPATH)
dma_PLATFORM_DEPENDENCY = yes
export dma_COMP_LIST
export dma_PLATFORM_DEPENDENCY
dma_PKG_LIST = dma
dma_INCLUDE = $(dma_PATH)/include $(dma_PATH)/$(MCAL_SOC_FILES)
dma_SOCLIST = $(DEFAULT_SOCLIST)
export dma_SOCLIST

############################
# mcu mcal lib
############################
mcu_COMP_LIST = mcu
mcu_RELPATH = Mcu
mcu_PATH = $(mcal_PATH)/$(mcu_RELPATH)
mcu_PLATFORM_DEPENDENCY = yes
export mcu_COMP_LIST
export mcu_PLATFORM_DEPENDENCY
mcu_PKG_LIST = mcu
mcu_INCLUDE = $(mcu_PATH)/include $(mcu_PATH)/$(MCAL_MCU_SOC_FILES)
mcu_SOCLIST = $(DEFAULT_SOCLIST)
export mcu_SOCLIST

############################
# Dio mcal lib
############################
dio_COMP_LIST = dio
dio_RELPATH = Dio
dio_PATH = $(mcal_PATH)/$(dio_RELPATH)
dio_PLATFORM_DEPENDENCY = yes
export dio_COMP_LIST
export dio_PLATFORM_DEPENDENCY
dio_PKG_LIST = dio
dio_INCLUDE = $(dio_PATH)/include $(dio_PATH)/$(MCAL_SOC_FILES)
dio_SOCLIST = $(DEFAULT_SOCLIST)
export dio_SOCLIST

############################
# i2c mcal lib
############################
export i2c_COMP_LIST = i2c
i2c_RELPATH = I2c
i2c_PATH = $(mcal_PATH)/$(i2c_RELPATH)
export i2c_PLATFORM_DEPENDENCY = yes
i2c_PKG_LIST = i2c
i2c_INCLUDE = $(i2c_PATH)/include
export i2c_SOCLIST = $(DEFAULT_SOCLIST)

############################
# port mcal lib
############################
port_COMP_LIST = port
port_RELPATH = Port
port_PATH = $(mcal_PATH)/$(port_RELPATH)
port_PLATFORM_DEPENDENCY = yes
export port_COMP_LIST
export port_PLATFORM_DEPENDENCY
port_PKG_LIST = port
port_INCLUDE = $(port_PATH)/include $(port_PATH)/$(MCAL_SOC_FILES)
port_SOCLIST = $(DEFAULT_SOCLIST)
export port_SOCLIST

############################
# gpt mcal lib
############################
gpt_COMP_LIST = gpt
gpt_RELPATH = Gpt
gpt_PATH = $(mcal_PATH)/$(gpt_RELPATH)
gpt_PLATFORM_DEPENDENCY = yes
export gpt_COMP_LIST
export gpt_PLATFORM_DEPENDENCY
gpt_PKG_LIST = gpt
gpt_INCLUDE = $(gpt_PATH)/include $(gpt_PATH)/$(MCAL_SOC_FILES)
gpt_SOCLIST = $(DEFAULT_SOCLIST)
export gpt_SOCLIST

############################
# wdg mcal lib
############################
wdg_COMP_LIST = wdg
wdg_RELPATH = Wdg
wdg_PATH = $(mcal_PATH)/$(wdg_RELPATH)
wdg_PLATFORM_DEPENDENCY = yes
export wdg_COMP_LIST
export wdg_PLATFORM_DEPENDENCY
wdg_PKG_LIST = wdg
wdg_INCLUDE = $(wdg_PATH)/include $(wdg_PATH)/$(MCAL_SOC_FILES)
wdg_SOCLIST = $(DEFAULT_SOCLIST)
export wdg_SOCLIST

############################
# spi mcal lib
############################
spi_COMP_LIST = spi
spi_RELPATH = Spi
spi_PATH = $(mcal_PATH)/$(spi_RELPATH)
spi_PLATFORM_DEPENDENCY = yes
export spi_COMP_LIST
export spi_PLATFORM_DEPENDENCY
spi_PKG_LIST = spi
spi_INCLUDE = $(spi_PATH)/include $(spi_PATH)/$(MCAL_SOC_FILES)
spi_SOCLIST = $(DEFAULT_SOCLIST)
export spi_SOCLIST

############################
# can mcal lib
############################
can_COMP_LIST = can
can_RELPATH = Can
can_PATH = $(mcal_PATH)/$(can_RELPATH)
can_PLATFORM_DEPENDENCY = yes
export can_COMP_LIST
export can_PLATFORM_DEPENDENCY
can_PKG_LIST = can
can_INCLUDE = $(can_PATH)/include $(can_PATH)/$(MCAL_SOC_FILES)
can_SOCLIST = $(DEFAULT_SOCLIST)
export can_SOCLIST

############################
# cdd_cmpss mcal lib
############################
cdd_cmpss_COMP_LIST = cdd_cmpss
cdd_cmpss_RELPATH = Cdd_Cmpss
cdd_cmpss_PATH = $(mcal_PATH)/$(cdd_cmpss_RELPATH)
cdd_cmpss_PLATFORM_DEPENDENCY = yes
export cdd_cmpss_COMP_LIST
export cdd_cmpss_PLATFORM_DEPENDENCY
cdd_cmpss_PKG_LIST = cdd_cmpss
cdd_cmpss_INCLUDE = $(cdd_cmpss_PATH)/include
cdd_cmpss_SOCLIST = $(DEFAULT_SOCLIST)
export cdd_cmpss_SOCLIST

############################
# cdd_flc mcal lib
############################
cdd_flc_COMP_LIST = cdd_flc
cdd_flc_RELPATH = Cdd_Flc
cdd_flc_PATH = $(mcal_PATH)/$(cdd_flc_RELPATH)
cdd_flc_PLATFORM_DEPENDENCY = yes
export cdd_flc_COMP_LIST
export cdd_flc_PLATFORM_DEPENDENCY
cdd_flc_PKG_LIST = cdd_flc
cdd_flc_INCLUDE = $(cdd_flc_PATH)/include
cdd_flc_SOCLIST = $(DEFAULT_SOCLIST)
export cdd_flc_SOCLIST

############################
# fls mcal lib
############################
fls_COMP_LIST = fls
fls_RELPATH = Fls
fls_PATH = $(mcal_PATH)/$(fls_RELPATH)
fls_PLATFORM_DEPENDENCY = yes
export fls_COMP_LIST
export fls_PLATFORM_DEPENDENCY
fls_PKG_LIST = fls
fls_INCLUDE = $(fls_PATH)/include $(fls_PATH)/$(MCAL_FLS_SOC_FILES)
fls_SOCLIST = $(DEFAULT_SOCLIST)
export fls_SOCLIST

############################
# pwm mcal lib
############################
pwm_COMP_LIST = pwm
pwm_RELPATH = Pwm
pwm_PATH = $(mcal_PATH)/$(pwm_RELPATH)
pwm_PLATFORM_DEPENDENCY = yes
export pwm_COMP_LIST
export pwm_PLATFORM_DEPENDENCY
pwm_PKG_LIST = pwm
pwm_INCLUDE = $(pwm_PATH)/include $(pwm_PATH)/$(MCAL_SOC_FILES)
pwm_SOCLIST = $(DEFAULT_SOCLIST)
export pwm_SOCLIST

############################
# icu mcal lib
############################
icu_COMP_LIST = icu
icu_RELPATH = Icu
icu_PATH = $(mcal_PATH)/$(icu_RELPATH)
icu_PLATFORM_DEPENDENCY = yes
export icu_COMP_LIST
export icu_PLATFORM_DEPENDENCY
icu_PKG_LIST = icu
icu_INCLUDE = $(icu_PATH)/include $(icu_PATH)/$(MCAL_SOC_FILES)
icu_SOCLIST = $(DEFAULT_SOCLIST)
export icu_SOCLIST

############################
# eth mcal lib
############################
eth_COMP_LIST = eth
eth_RELPATH = Eth
eth_PATH = $(mcal_PATH)/$(eth_RELPATH)
eth_PLATFORM_DEPENDENCY = yes
export eth_COMP_LIST
export eth_PLATFORM_DEPENDENCY
eth_PKG_LIST = eth
eth_INCLUDE = $(eth_PATH)/include $(eth_PATH)/$(MCAL_SOC_FILES)
eth_SOCLIST = $(DEFAULT_SOCLIST)
export eth_SOCLIST

############################
# ethtrcv mcal lib
############################
ethtrcv_COMP_LIST = ethtrcv
ethtrcv_RELPATH = EthTrcv
ethtrcv_PATH = $(mcal_PATH)/$(ethtrcv_RELPATH)
ethtrcv_PLATFORM_DEPENDENCY = yes
export ethtrcv_COMP_LIST
export ethtrcv_PLATFORM_DEPENDENCY
ethtrcv_PKG_LIST = ethtrcv
ethtrcv_INCLUDE = $(ethtrcv_PATH)/include $(ethtrcv_PATH)/$(MCAL_SOC_FILES)
ethtrcv_SOCLIST = $(DEFAULT_SOCLIST)
export ethtrcv_SOCLIST

############################
# adc mcal lib
############################
adc_COMP_LIST = adc
adc_RELPATH = Adc
adc_PATH = $(mcal_PATH)/$(adc_RELPATH)
adc_PLATFORM_DEPENDENCY = yes
export adc_COMP_LIST
export adc_PLATFORM_DEPENDENCY
adc_PKG_LIST = adc
adc_INCLUDE = $(adc_PATH)/include $(adc_PATH)/$(MCAL_SOC_FILES)
adc_SOCLIST = $(DEFAULT_SOCLIST)
export adc_SOCLIST

############################
# fsitx mcal lib
############################
fsitx_COMP_LIST = fsitx
fsitx_RELPATH = FsiTx
fsitx_PATH = $(mcal_PATH)/$(fsitx_RELPATH)
fsitx_PLATFORM_DEPENDENCY = yes
export fsitx_COMP_LIST
export fsitx_PLATFORM_DEPENDENCY
fsitx_PKG_LIST = fsitx
fsitx_INCLUDE = $(fsitx_PATH)/include $(fsitx_PATH)/$(MCAL_SOC_FILES)
fsitx_SOCLIST = $(DEFAULT_SOCLIST)
export fsitx_SOCLIST

############################
# fsirx mcal lib
############################
fsirx_COMP_LIST = fsirx
fsirx_RELPATH = FsiRx
fsirx_PATH = $(mcal_PATH)/$(fsirx_RELPATH)
fsirx_PLATFORM_DEPENDENCY = yes
export fsirx_COMP_LIST
export fsirx_PLATFORM_DEPENDENCY
fsirx_PKG_LIST = fsirx
fsirx_INCLUDE = $(fsirx_PATH)/include $(fsirx_PATH)/$(MCAL_SOC_FILES)
fsirx_SOCLIST = $(DEFAULT_SOCLIST)
export fsirx_SOCLIST

############################
# ipc mcal lib
############################
ipc_COMP_LIST = ipc
ipc_RELPATH = Ipc
ipc_PATH = $(mcal_PATH)/$(ipc_RELPATH)
ipc_PLATFORM_DEPENDENCY = yes
export ipc_COMP_LIST
export ipc_PLATFORM_DEPENDENCY
ipc_PKG_LIST = ipc
ipc_INCLUDE = $(ipc_PATH)/include $(ipc_PATH)/$(MCAL_SOC_FILES)
ipc_SOCLIST = $(DEFAULT_SOCLIST)
export ipc_SOCLIST

############################
# uart mcal lib
############################
uart_COMP_LIST = uart
uart_RELPATH = Uart
uart_PATH = $(mcal_PATH)/$(uart_RELPATH)
uart_PLATFORM_DEPENDENCY = yes
export uart_COMP_LIST
export uart_PLATFORM_DEPENDENCY
uart_PKG_LIST = uart
uart_INCLUDE = $(uart_PATH)/include $(uart_PATH)/$(MCAL_SOC_FILES)
uart_SOCLIST = $(DEFAULT_SOCLIST)
export uart_SOCLIST

############################
# Lin mcal lib
############################
lin_COMP_LIST = lin
lin_RELPATH = Lin
lin_PATH = $(mcal_PATH)/$(lin_RELPATH)
lin_PLATFORM_DEPENDENCY = yes
export lin_COMP_LIST
export lin_PLATFORM_DEPENDENCY
lin_PKG_LIST = lin
lin_INCLUDE = $(lin_PATH)/include $(lin_PATH)/$(MCAL_SOC_FILES)
lin_SOCLIST = $(DEFAULT_SOCLIST)
export lin_SOCLIST

############################
# CDD PWM mcal lib
############################
epwm_COMP_LIST = epwm
epwm_RELPATH = Epwm
epwm_PATH = $(mcal_PATH)/$(epwm_RELPATH)
epwm_PLATFORM_DEPENDENCY = yes
export epwm_COMP_LIST
export epwm_PLATFORM_DEPENDENCY
epwm_PKG_LIST = epwm
epwm_INCLUDE = $(epwm_PATH)/include $(epwm_PATH)/$(MCAL_SOC_FILES)
epwm_SOCLIST = $(DEFAULT_SOCLIST)
export epwm_SOCLIST

############################
#device mcal examples
# List of examples under mcal
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################

ifeq ($(PLATFORM),$(filter $(PLATFORM), am263))
mcal_mcal_EXAMPLE_LIST = mcu_app gpt_app mcspi_app can_app port_app dio_app wdg_app wdg_skip_reset_app fls_app eth_app eth_test_app adc_app adc_hw_trig_dma_app pwm_app icu_app ipc_notify_app ipc_rpmsg_app ipc_rpmsg_callback_app i2c_app i2c_intr_app i2c_multichannel_app uart_echo_dma_app fsirx_app lin_app flsdiag_app epwm_app epwm_tz_app dma_interruptmode_app dma_linkingmode_app dma_pollingmode_app dma_chainingmode_app cdd_cmpss_app
mcal_mcal_APP_LIB_LIST += app_utils
mcal_mcal_KW_LIST = kwadc kwcan kwdio kwdma kweth kwethtrcv kwcmpss kwfls kwgpt kwi2c kwicu kwipc kwmcu kwspi kwpwm kwepwm kwuart kwwdg kwport kwfsirx kwfsitx kwlin
endif

ifeq ($(PLATFORM),$(filter $(PLATFORM), am263px))
mcal_mcal_EXAMPLE_LIST = mcu_app fls_boot_app gpt_app mcspi_app can_app port_app dio_app wdg_app wdg_skip_reset_app adc_app adc_resolver_app adc_resolver_dma_app adc_hw_trig_dma_app eth_app eth_test_app pwm_app icu_app ipc_notify_app ipc_rpmsg_app ipc_rpmsg_callback_app i2c_app i2c_intr_app i2c_multichannel_app uart_echo_dma_app fsirx_app lin_app dma_interruptmode_app dma_linkingmode_app dma_pollingmode_app dma_chainingmode_app fls_app flsdiag_ospi_app epwm_app epwm_tz_app cdd_flc_app cdd_cmpss_app
mcal_mcal_APP_LIB_LIST += app_utils
mcal_mcal_KW_LIST = kwadc kwcan kwdio kwdma kweth kwethtrcv kwcmpss kwflc kwfls kwgpt kwi2c kwicu kwipc kwmcu kwspi kwpwm kwepwm kwuart kwwdg kwport kwfsirx kwfsitx kwlin
endif

ifeq ($(PLATFORM),$(filter $(PLATFORM), am261))
mcal_mcal_EXAMPLE_LIST = mcu_app gpt_app mcspi_app can_app port_app dio_app wdg_app wdg_skip_reset_app fls_app eth_app eth_test_app adc_app adc_hw_trig_dma_app pwm_app icu_app ipc_notify_app ipc_rpmsg_app ipc_rpmsg_callback_app i2c_app i2c_intr_app i2c_multichannel_app uart_interrupt_app dma_interruptmode_app dma_linkingmode_app dma_pollingmode_app dma_chainingmode_app flsdiag_ospi_app lin_app epwm_app fsirx_app cdd_flc_app cdd_cmpss_app
mcal_mcal_APP_LIB_LIST += app_utils
mcal_mcal_KW_LIST = kwadc kwcan kwdio kwdma kweth kwethtrcv kwcmpss kwflc kwfls kwgpt kwi2c kwicu kwipc kwmcu kwspi kwpwm kwuart kwwdg kwport kwlin kwepwm kwfsirx kwfsitx
endif

ifneq ($(MCUPLUSSDK_ROOTDIR), )
mcal_mcal_EXAMPLE_LIST += eth_load_app
endif

##############################
mcu_app_RELPATH = examples/Mcu
mcu_app_PATH = $(mcal_PATH)/$(mcu_app_RELPATH)
mcu_app_PLATFORM_DEPENDENCY = yes
mcu_app_SOCLIST = $(DEFAULT_SOCLIST)
export mcu_app_SOCLIST
export mcu_app_PLATFORM_DEPENDENCY

pwm_app_RELPATH = examples/Pwm
pwm_app_PATH = $(mcal_PATH)/$(pwm_app_RELPATH)
pwm_app_PLATFORM_DEPENDENCY = yes
pwm_app_SOCLIST = $(DEFAULT_SOCLIST)
export pwm_app_SOCLIST
export pwm_app_PLATFORM_DEPENDENCY

gpt_app_RELPATH = examples/Gpt
gpt_app_PATH = $(mcal_PATH)/$(gpt_app_RELPATH)
gpt_app_PLATFORM_DEPENDENCY = yes
gpt_app_SOCLIST = $(DEFAULT_SOCLIST)
export gpt_app_SOCLIST
export gpt_app_PLATFORM_DEPENDENCY

i2c_app_RELPATH = examples/I2c/i2c_app
i2c_app_PATH = $(mcal_PATH)/$(i2c_app_RELPATH)
export i2c_app_PLATFORM_DEPENDENCY = yes
export i2c_app_SOCLIST = $(DEFAULT_SOCLIST)

i2c_intr_app_RELPATH = examples/I2c/i2c_intr_app
i2c_intr_app_PATH = $(mcal_PATH)/$(i2c_intr_app_RELPATH)
export i2c_intr_app_PLATFORM_DEPENDENCY = yes
export i2c_intr_app_SOCLIST = $(DEFAULT_SOCLIST)

i2c_multichannel_app_RELPATH = examples/I2c/i2c_multichannel_app
i2c_multichannel_app_PATH = $(mcal_PATH)/$(i2c_multichannel_app_RELPATH)
export i2c_multichannel_app_PLATFORM_DEPENDENCY = yes
export i2c_multichannel_app_SOCLIST = $(DEFAULT_SOCLIST)

dio_app_RELPATH = examples/Dio
dio_app_PATH = $(mcal_PATH)/$(dio_app_RELPATH)
dio_app_PLATFORM_DEPENDENCY = yes
dio_app_SOCLIST = $(DEFAULT_SOCLIST)
export dio_app_SOCLIST
export dio_app_PLATFORM_DEPENDENCY

wdg_app_RELPATH = examples/Wdg/wdg_app
wdg_app_PATH = $(mcal_PATH)/$(wdg_app_RELPATH)
wdg_app_PLATFORM_DEPENDENCY = yes
wdg_app_SOCLIST = $(DEFAULT_SOCLIST)
export wdg_app_SOCLIST
export wdg_app_PLATFORM_DEPENDENCY

wdg_skip_reset_app_RELPATH = examples/Wdg/wdg_skip_reset_app
wdg_skip_reset_app_PATH = $(mcal_PATH)/$(wdg_skip_reset_app_RELPATH)
export wdg_skip_reset_app_PLATFORM_DEPENDENCY = yes
export wdg_skip_reset_app_SOCLIST = $(DEFAULT_SOCLIST)

fls_app_RELPATH = examples/Fls
fls_app_PATH = $(mcal_PATH)/$(fls_app_RELPATH)
fls_app_PLATFORM_DEPENDENCY = yes
fls_app_SOCLIST = $(DEFAULT_SOCLIST)
export fls_app_SOCLIST
export fls_app_PLATFORM_DEPENDENCY

fls_boot_app_RELPATH = examples/Bootloader/fls_boot_app
fls_boot_app_PATH = $(mcal_PATH)/$(fls_boot_app_RELPATH)
fls_boot_app_PLATFORM_DEPENDENCY = yes
fls_boot_app_SOCLIST = $(DEFAULT_SOCLIST)
export fls_boot_app_SOCLIST
export fls_boot_app_PLATFORM_DEPENDENCY

flsdiag_app_RELPATH = examples/Flsdiag
flsdiag_app_PATH = $(mcal_PATH)/$(flsdiag_app_RELPATH)
flsdiag_app_PLATFORM_DEPENDENCY = yes
flsdiag_app_SOCLIST = $(DEFAULT_SOCLIST)
export flsdiag_app_SOCLIST
export flsdiag_app_PLATFORM_DEPENDENCY

flsdiag_ospi_app_RELPATH = examples/Flsdiag_ospi
flsdiag_ospi_app_PATH = $(mcal_PATH)/$(flsdiag_ospi_app_RELPATH)
flsdiag_ospi_app_PLATFORM_DEPENDENCY = yes
flsdiag_ospi_app_SOCLIST = $(DEFAULT_SOCLIST)
export flsdiag_ospi_app_SOCLIST
export flsdiag_opsi_app_PLATFORM_DEPENDENCY

mcspi_app_RELPATH = examples/Spi/mcspi_app
mcspi_app_PATH = $(mcal_PATH)/$(mcspi_app_RELPATH)
mcspi_app_PLATFORM_DEPENDENCY = yes
mcspi_app_SOCLIST = $(DEFAULT_SOCLIST)
export mcspi_app_SOCLIST
export mcspi_app_PLATFORM_DEPENDENCY

qspi_flash_app_RELPATH = examples/Spi/qspi_flash_app
qspi_flash_app_PATH = $(mcal_PATH)/$(qspi_flash_app_RELPATH)
qspi_flash_app_PLATFORM_DEPENDENCY = yes
qspi_flash_app_SOCLIST = $(DEFAULT_SOCLIST)
export qspi_flash_app_SOCLIST
export qspi_flash_app_PLATFORM_DEPENDENCY

mibspi_app_RELPATH = examples/Spi/mibspi_app
mibspi_app_PATH = $(mcal_PATH)/$(mibspi_app_RELPATH)
mibspi_app_PLATFORM_DEPENDENCY = yes
mibspi_app_SOCLIST = $(DEFAULT_SOCLIST)
export mibspi_app_SOCLIST
export mibspi_app_PLATFORM_DEPENDENCY

can_app_RELPATH = examples/Can
can_app_PATH = $(mcal_PATH)/$(can_app_RELPATH)
can_app_PLATFORM_DEPENDENCY = yes
can_app_SOCLIST = $(DEFAULT_SOCLIST)
export can_app_SOCLIST
export can_app_PLATFORM_DEPENDENCY

port_app_RELPATH = examples/Port
port_app_PATH = $(mcal_PATH)/$(port_app_RELPATH)
port_app_PLATFORM_DEPENDENCY = yes
port_app_SOCLIST = $(DEFAULT_SOCLIST)
export port_app_SOCLIST
export port_app_PLATFORM_DEPENDENCY

dio_app_RELPATH = examples/Dio
dio_app_PATH = $(mcal_PATH)/$(dio_app_RELPATH)
dio_app_PLATFORM_DEPENDENCY = yes
dio_app_SOCLIST = $(DEFAULT_SOCLIST)
export dio_app_SOCLIST
export dio_app_PLATFORM_DEPENDENCY

icu_app_RELPATH = examples/Icu
icu_app_PATH = $(mcal_PATH)/$(icu_app_RELPATH)
icu_app_PLATFORM_DEPENDENCY = yes
icu_app_SOCLIST = $(DEFAULT_SOCLIST)
export icu_app_SOCLIST
export icu_app_PLATFORM_DEPENDENCY

eth_app_RELPATH = examples/Eth/eth_app
eth_app_PATH = $(mcal_PATH)/$(eth_app_RELPATH)
eth_app_PLATFORM_DEPENDENCY = yes
eth_app_SOCLIST = $(DEFAULT_SOCLIST)
export eth_app_SOCLIST
export eth_app_PLATFORM_DEPENDENCY

eth_test_app_RELPATH = examples/Eth/eth_test_app
eth_test_app_PATH = $(mcal_PATH)/$(eth_test_app_RELPATH)
eth_test_app_PLATFORM_DEPENDENCY = yes
eth_test_app_SOCLIST = $(DEFAULT_SOCLIST)
export eth_test_app_SOCLIST
export eth_test_app_PLATFORM_DEPENDENCY

eth_load_app_RELPATH = examples/Eth/eth_load_app
eth_load_app_PATH = $(mcal_PATH)/$(eth_load_app_RELPATH)
eth_load_app_PLATFORM_DEPENDENCY = yes
eth_load_app_SOCLIST = $(DEFAULT_SOCLIST)
export eth_load_app_SOCLIST
export eth_load_app_PLATFORM_DEPENDENCY

adc_app_RELPATH = examples/Adc/adc_app
adc_app_PATH = $(mcal_PATH)/$(adc_app_RELPATH)
adc_app_PLATFORM_DEPENDENCY = yes
adc_app_SOCLIST = $(DEFAULT_SOCLIST)
export adc_app_SOCLIST
export adc_app_PLATFORM_DEPENDENCY

adc_resolver_app_RELPATH = examples/Adc/adc_resolver_app
adc_resolver_app_PATH = $(mcal_PATH)/$(adc_resolver_app_RELPATH)
adc_resolver_app_PLATFORM_DEPENDENCY = yes
adc_resolver_app_SOCLIST = am263px
export adc_resolver_app_SOCLIST
export adc_resolver_app_PLATFORM_DEPENDENCY

adc_resolver_dma_app_RELPATH = examples/Adc/adc_resolver_dma_app
adc_resolver_dma_app_PATH = $(mcal_PATH)/$(adc_resolver_dma_app_RELPATH)
adc_resolver_dma_app_PLATFORM_DEPENDENCY = yes
adc_resolver_dma_app_SOCLIST = am263px
export adc_resolver_dma_app_SOCLIST
export adc_resolver_dma_app_PLATFORM_DEPENDENCY

adc_hw_trig_dma_app_RELPATH = examples/Adc/adc_hw_trig_dma_app
adc_hw_trig_dma_app_PATH = $(mcal_PATH)/$(adc_hw_trig_dma_app_RELPATH)
adc_hw_trig_dma_app_PLATFORM_DEPENDENCY = yes
adc_hw_trig_dma_app_SOCLIST = $(DEFAULT_SOCLIST)
export adc_hw_trig_dma_app_SOCLIST
export adc_hw_trig_dma_app_PLATFORM_DEPENDENCY

cdd_cmpss_app_RELPATH = examples/Cdd_Cmpss
cdd_cmpss_app_PATH = $(mcal_PATH)/$(cdd_cmpss_app_RELPATH)
cdd_cmpss_app_PLATFORM_DEPENDENCY = yes
cdd_cmpss_app_SOCLIST = $(DEFAULT_SOCLIST)
export cdd_cmpss_app_SOCLIST
export cdd_cmpss_app_PLATFORM_DEPENDENCY

cdd_flc_app_RELPATH = examples/Cdd_Flc
cdd_flc_app_PATH = $(mcal_PATH)/$(cdd_flc_app_RELPATH)
cdd_flc_app_PLATFORM_DEPENDENCY = yes
cdd_flc_app_SOCLIST = $(DEFAULT_SOCLIST)
export cdd_flc_app_SOCLIST
export cdd_flc_app_PLATFORM_DEPENDENCY

fsitx_app_RELPATH = examples/FsiTx
fsitx_app_PATH = $(mcal_PATH)/$(fsitx_app_RELPATH)
fsitx_app_PLATFORM_DEPENDENCY = yes
fsitx_app_SOCLIST = $(DEFAULT_SOCLIST)
export fsitx_app_SOCLIST
export fsitx_app_PLATFORM_DEPENDENCY

fsirx_app_RELPATH = examples/FsiRx
fsirx_app_PATH = $(mcal_PATH)/$(fsirx_app_RELPATH)
fsirx_app_PLATFORM_DEPENDENCY = yes
fsirx_app_SOCLIST = $(DEFAULT_SOCLIST)
export fsirx_app_SOCLIST
export fsirx_app_PLATFORM_DEPENDENCY

uart_interrupt_app_RELPATH = examples/Uart/uart_interrupt_app
uart_interrupt_app_PATH = $(mcal_PATH)/$(uart_interrupt_app_RELPATH)
uart_interrupt_app_PLATFORM_DEPENDENCY = yes
uart_interrupt_app_SOCLIST = $(DEFAULT_SOCLIST)
export uart_interrupt_app_SOCLIST
export uart_interrupt_app_PLATFORM_DEPENDENCY

uart_echo_dma_app_RELPATH = examples/Uart/uart_echo_dma_app
uart_echo_dma_app_PATH = $(mcal_PATH)/$(uart_echo_dma_app_RELPATH)
uart_echo_dma_app_PLATFORM_DEPENDENCY = yes
uart_echo_dma_app_SOCLIST = $(DEFAULT_SOCLIST)
export uart_echo_dma_app_SOCLIST
export uart_echo_dma_app_PLATFORM_DEPENDENCY

ipc_notify_app_RELPATH = examples/Ipc/Ipc_app_notify
ipc_notify_app_PATH = $(mcal_PATH)/$(ipc_notify_app_RELPATH)
ipc_notify_app_PLATFORM_DEPENDENCY = yes
ipc_notify_app_SOCLIST = $(DEFAULT_SOCLIST)
export ipc_notify_app_SOCLIST
export ipc_notify_app_PLATFORM_DEPENDENCY

ipc_rpmsg_app_RELPATH = examples/Ipc/Ipc_app_rpmsg
ipc_rpmsg_app_PATH = $(mcal_PATH)/$(ipc_rpmsg_app_RELPATH)
ipc_rpmsg_app_PLATFORM_DEPENDENCY = yes
ipc_rpmsg_app_SOCLIST = $(DEFAULT_SOCLIST)
export ipc_rpmsg_app_SOCLIST
export ipc_rpmsg_app_PLATFORM_DEPENDENCY

ipc_rpmsg_callback_app_RELPATH = examples/Ipc/Ipc_app_rpmsg_callback_mode
ipc_rpmsg_callback_app_PATH = $(mcal_PATH)/$(ipc_rpmsg_callback_app_RELPATH)
ipc_rpmsg_callback_app_PLATFORM_DEPENDENCY = yes
ipc_rpmsg_callback_app_SOCLIST = $(DEFAULT_SOCLIST)
export ipc_rpmsg_app_SOCLIST
export ipc_rpmsg_app_PLATFORM_DEPENDENCY

ipc_safeipc_app_RELPATH = examples/Ipc/Ipc_app_safeipc
ipc_safeipc_app_PATH = $(mcal_PATH)/$(ipc_safeipc_app_RELPATH)
ipc_safeipc_app_PLATFORM_DEPENDENCY = yes
ipc_safeipc_app_SOCLIST = $(DEFAULT_SOCLIST)
export ipc_safeipc_app_SOCLIST
export ipc_safeipc_app_PLATFORM_DEPENDENCY

ipc_safeipc_test_RELPATH = examples/Ipc/Ipc_test_safeipc
ipc_safeipc_test_PATH = $(mcal_PATH)/$(ipc_safeipc_test_RELPATH)
ipc_safeipc_test_PLATFORM_DEPENDENCY = yes
ipc_safeipc_test_SOCLIST = $(DEFAULT_SOCLIST)
export ipc_safeipc_test_SOCLIST
export ipc_safeipc_test_PLATFORM_DEPENDENCY

lin_app_RELPATH = examples/Lin
lin_app_PATH = $(mcal_PATH)/$(lin_app_RELPATH)
lin_app_PLATFORM_DEPENDENCY = yes
lin_app_SOCLIST = $(DEFAULT_SOCLIST)
export lin_app_SOCLIST
export lin_app_PLATFORM_DEPENDENCY

epwm_app_RELPATH = examples/Epwm/epwm_app
epwm_app_PATH = $(mcal_PATH)/$(epwm_app_RELPATH)
epwm_app_PLATFORM_DEPENDENCY = yes
epwm_app_SOCLIST = $(DEFAULT_SOCLIST)
export epwm_app_SOCLIST
export epwm_app_PLATFORM_DEPENDENCY

epwm_tz_app_RELPATH = examples/Epwm/epwm_tz_app
epwm_tz_app_PATH = $(mcal_PATH)/$(epwm_tz_app_RELPATH)
epwm_tz_app_PLATFORM_DEPENDENCY = yes
epwm_tz_app_SOCLIST = $(DEFAULT_SOCLIST)
export epwm_tz_app_SOCLIST
export epwm_tz_app_PLATFORM_DEPENDENCY

dma_interruptmode_app_RELPATH = examples/Dma/Dma_InterruptMode
dma_interruptmode_app_PATH = $(mcal_PATH)/$(dma_interruptmode_app_RELPATH)
dma_interruptmode_app_PLATFORM_DEPENDENCY = yes
dma_interruptmode_app_SOCLIST = $(DEFAULT_SOCLIST)
export dma_interruptmode_app_SOCLIST
export dma_interruptmode_app_PLATFORM_DEPENDENCY

dma_linkingmode_app_RELPATH = examples/Dma/Dma_LinkingMode
dma_linkingmode_app_PATH = $(mcal_PATH)/$(dma_linkingmode_app_RELPATH)
dma_linkingmode_app_PLATFORM_DEPENDENCY = yes
dma_linkingmode_app_SOCLIST = $(DEFAULT_SOCLIST)
export dma_linkingmode_app_SOCLIST
export dma_linkingmode_app_PLATFORM_DEPENDENCY

dma_pollingmode_app_RELPATH = examples/Dma/Dma_PollingMode
dma_pollingmode_app_PATH = $(mcal_PATH)/$(dma_pollingmode_app_RELPATH)
dma_pollingmode_app_PLATFORM_DEPENDENCY = yes
dma_pollingmode_app_SOCLIST = $(DEFAULT_SOCLIST)
export dma_pollingmode_app_SOCLIST
export dma_pollingmode_app_PLATFORM_DEPENDENCY

dma_chainingmode_app_RELPATH = examples/Dma/Dma_ChainingMode
dma_chainingmode_app_PATH = $(mcal_PATH)/$(dma_chainingmode_app_RELPATH)
dma_chainingmode_app_PLATFORM_DEPENDENCY = yes
dma_chainingmode_app_SOCLIST = $(DEFAULT_SOCLIST)
export dma_chainingmode_app_SOCLIST
export dma_chainingmode_app_PLATFORM_DEPENDENCY
##################################

bootloader_utils_COMP_LIST = bootloader_utils
bootloader_utils_RELPATH = examples/Utils/bootloader_utils
bootloader_utils_PATH = $(mcal_PATH)/$(bootloader_utils_RELPATH)
bootloader_utils_PLATFORM_DEPENDENCY = yes
export bootloader_utils_COMP_LIST
export bootloader_utils_PLATFORM_DEPENDENCY
bootloader_utils_PKG_LIST = bootloader_utils
bootloader_utils_INCLUDE = examples/Utils/bootloader_utils
bootloader_utils_SOCLIST = $(DEFAULT_SOCLIST)
export bootloader_utils_SOCLIST

app_utils_COMP_LIST = app_utils
app_utils_RELPATH = examples/Utils
app_utils_PATH = $(mcal_PATH)/$(app_utils_RELPATH)
app_utils_PLATFORM_DEPENDENCY = yes
app_utils_SOCLIST = $(DEFAULT_SOCLIST)
export app_utils_SOCLIST
export app_utils_PLATFORM_DEPENDENCY
export app_utils_COMP_LIST
app_utils_PKG_LIST = app_utils
app_utils_INCLUDE = $(app_utils_PATH) $(app_utils_PATH)/$(SOC) $(app_utils_PATH)/$(SOC) $(app_utils_PATH)/$(COMPILER) $(app_utils_PATH)/$(COMPILER)/$(SOC)

export mcal_mcal_LIB_LIST
export mcal_mcal_APP_LIB_LIST
export mcal_mcal_EXAMPLE_LIST
export mcal_mcal_dup_EXAMPLE_LIST

mcal_PKG_LIST_ALL = $(mcal_mcal_LIB_LIST) $(mcal_mcal_APP_LIB_LIST) $(mcal_mcal_EXAMPLE_LIST) $(mcal_mcal_dup_EXAMPLE_LIST)

mcal_component_make_include := 1
endif
# Nothing beyond this point
