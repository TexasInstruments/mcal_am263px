ifeq ($(OS),Windows_NT)
	SHELL=C:/Windows/System32/cmd.exe
endif
include Rules.make

MCAL_EXAMPLES = $(mcal_PATH)/examples

SOCFAMILY_LIST_DEFAULT = am263 am273 am263px am261

mcal_LIB_LIST_CLEAN = $(addsuffix _clean, $(mcal_LIB_LIST))
mcal_APP_LIB_LIST_CLEAN = $(addsuffix _clean, $(mcal_APP_LIB_LIST))
mcal_EXAMPLE_LIST_CLEAN = $(addsuffix _clean, $(mcal_EXAMPLE_LIST))
mcal_test_EXAMPLE_LIST_CLEAN = $(addsuffix _clean, $(mcal_test_EXAMPLE_LIST))
mcal_PKG_LIST_ALL_CLEAN = $(addsuffix _clean, $(mcal_PKG_LIST_ALL))

.PHONY : mcal_libs mcal_libs_clean unit_test unit_test_clean examples examples_clean kw_list all allkw testall clean gen_memstats $(mcal_PKG_LIST_ALL) allclean scrub

version:
	$(ECHO) ------------------------------------------------------
	$(ECHO) \# $(PLATFORM) MCAL 11.00.00
	$(ECHO) ------------------------------------------------------

mcal_libs: $(mcal_LIB_LIST)

mcal_libs_clean: $(mcal_LIB_LIST_CLEAN)

mcal_app_libs: $(mcal_APP_LIB_LIST)

mcal_app_libs_clean: $(mcal_APP_LIB_LIST_CLEAN)

unit_test: $(mcal_test_EXAMPLE_LIST)
unit_test_clean: $(mcal_test_EXAMPLE_LIST_CLEAN)

examples: $(mcal_EXAMPLE_LIST)

examples_clean: $(mcal_EXAMPLE_LIST_CLEAN)

kw_list: $(mcal_KW_LIST)

all: version mcal_libs mcal_app_libs
	$(MAKE) examples

allkw: version mcal_libs kw_list

testall: version mcal_libs mcal_app_libs
	$(MAKE) unit_test

clean: mcal_libs_clean mcal_app_libs_clean unit_test_clean examples_clean

allclean:
	$(RM) -rf $(DEST_ROOT)

scrub:
	$(RM) -rf $(mcal_PATH)/binary

help:
	$(ECHO) ------------------------------------------------------
	$(ECHO) \# MCAL make help
	$(ECHO) ------------------------------------------------------
	$(ECHO) gmake -s [OPTIONAL MAKE VARIABLES]
	$(ECHO)
	$(ECHO) "Supported targets:"
	$(ECHO) "------------------"
	$(ECHO) "all         : Builds all libraries and examples"
	$(ECHO) "allkw       : Builds all kw targets"
	$(ECHO) "clean       : Cleans all libraries and examples"
	$(ECHO) "allclean    : Removes the binary directory using rm -rf"
	$(ECHO) "examples    : Builds all examples"
	$(ECHO) "mcal_libs   : Builds all libraries"
	$(ECHO) "<Module>    : Builds a module:$(mcal_LIB_LIST)"
	$(ECHO) "<Module_App>: Builds a app:$(mcal_EXAMPLE_LIST)"
	$(ECHO) ""
	$(ECHO) "Optional make variables:"
	$(ECHO) "------------------------"
	$(ECHO) "PLATFORM=[am263, am273, am2732s, am263px, am261]"
	$(ECHO) "    Default: $(PLATFORM)"
	$(ECHO) "CORE=[r4 / r5f]"
	$(ECHO) "    Default: r5f"
	$(ECHO) "PROFILE=[debug / release]"
	$(ECHO) "    Default: release"
	$(ECHO) "BUILD_VARIANT=[precompile linktime postbuild]"
	$(ECHO) "    Default: precompile"
	$(ECHO) "OS=[Windows_NT / linux]"
	$(ECHO) "    Default: Windows_NT"
	$(ECHO) "COMPILER_SELECT=[CLANG / DIAB / TI_COMPILER]"
	$(ECHO) "    Default: CLANG"
	$(ECHO) "JENKINS_TEST_AUTOMATION=[TRUE / FALSE]"
	$(ECHO) "    Default: FALSE"

platforms:
	$(MAKE) all PLATFORM=am263
	$(MAKE) all PLATFORM=am273
	$(MAKE) all PLATFORM=am2732s
	$(MAKE) all PLATFORM=am263px
	$(MAKE) all PLATFORM=am261

platformsclean:
	$(MAKE) clean PLATFORM=am263
	$(MAKE) clean PLATFORM=am273
	$(MAKE) clean PLATFORM=am2732s
	$(MAKE) clean PLATFORM=am263px
	$(MAKE) clean PLATFORM=am261

profiles:
	$(MAKE) all PROFILE_$(CORE)=debug
	$(MAKE) all PROFILE_$(CORE)=release

profilesclean:
	$(MAKE) clean PROFILE_$(CORE)=debug
	$(MAKE) clean PROFILE_$(CORE)=release

allall:
	$(MAKE) platforms PROFILE_$(CORE)=debug
	$(MAKE) platforms PROFILE_$(CORE)=release

#=================================================================
#These targets are for use with Klockwork only
kwadc:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(adc_SOCLIST))),$(MAKE) -C $(adc_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) adc)

kwcan:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(can_SOCLIST))),$(MAKE) -C $(can_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) can)

kwcmpss:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(cdd_cmpss_SOCLIST))),$(MAKE) -C $(cdd_cmpss_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) cmpss)

kwdio:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(dio_SOCLIST))),$(MAKE) -C $(dio_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) dio)

kwdma:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(dma_SOCLIST))),$(MAKE) -C $(dma_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) dma)

kweth:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(eth_SOCLIST))),$(MAKE) -C $(eth_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) eth)

kwethtrcv:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(ethtrcv_SOCLIST))),$(MAKE) -C $(ethtrcv_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) ethtrcv)

kwflc:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(cdd_flc_SOCLIST))),$(MAKE) -C $(cdd_flc_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) flc)

kwfls:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(fls_SOCLIST))),$(MAKE) -C $(fls_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) fls)

kwfsirx:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(fsirx_SOCLIST))),$(MAKE) -C $(fsirx_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) fsirx)

kwfsitx:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(fsitx_SOCLIST))),$(MAKE) -C $(fsitx_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) fsitx)

kwgpt:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(gpt_SOCLIST))),$(MAKE) -C $(gpt_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) gpt)

kwi2c:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(i2c_SOCLIST))),$(MAKE) -C $(i2c_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) i2c)

kwicu:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(icu_SOCLIST))),$(MAKE) -C $(icu_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) icu)

kwipc:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(ipc_SOCLIST))),$(MAKE) -C $(ipc_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) ipc)

kwlin:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(lin_SOCLIST))),$(MAKE) -C $(lin_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) lin)

kwmcu:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(mcu_SOCLIST))),$(MAKE) -C $(mcu_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) mcu)

kwspi:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(spi_SOCLIST))),$(MAKE) -C $(spi_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) spi)

kwpwm:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(pwm_SOCLIST))),$(MAKE) -C $(pwm_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) pwm)

kwepwm:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(epwm_SOCLIST))),$(MAKE) -C $(epwm_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) epwm)

kwuart:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(uart_SOCLIST))),$(MAKE) -C $(uart_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) uart)

kwwdg:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(wdg_SOCLIST))),$(MAKE) -C $(wdg_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) wdg)

kwport:
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$(port_SOCLIST))),$(MAKE) -C $(port_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) port)

#=================================================================
# MCALs libs and tests
$(mcal_PKG_LIST_ALL):
	$(if $(filter $(SOCFAMILY), $(subst emptyreplacement,,$($@_SOCLIST))),$(MAKE) -C $($@_PATH),$(ECHO) Nothing to be done for $(SOCFAMILY) $@)

$(mcal_PKG_LIST_ALL_CLEAN):
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean

# Below is used only for checking c++ build errors during development, not to be used for any other purpose
cplusplus_build:
	$(MAKE) all PROFILE=debug CPLUSPLUS_BUILD=yes

gen_memstats: mcal_libs
	cmd /c ..\mcal_misc\docs\memStats\mcal_run_all.sh $(COMPILER) $(PLATFORM) $(CORE) $(PROFILE)

# Nothing beyond this point
