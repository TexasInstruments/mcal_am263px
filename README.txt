
Steps to build
==============

- Open Rules.make

- Edit paths for the below variables according to your system environment

  In case of windows machine edit below paths,

  TOOLCHAIN_R5_VERSION=ti-cgt-armllvm_x.x.x.LTS
  CCS_PATH := C:/ti/ccsxxxx/ccs

  In case of linux machine edit the similar linux paths and pass OS=linux while invoking any make command.

  IMPORTANT:
  Make sure the paths specified above DO NOT have any spaces in them.

- Make sure "gmake" is in your system path.
  Typically when CCS is installed "gmake" is installed along with it and
  it becomes part of the system path by default.

- Install dependencies required for MCELF image format
  Install OpenSSL v3 from here: "https://slproweb.com/products/Win32OpenSSL.html"
  Install Python3
  Install Pip
  Make sure pyelftools and construct is installed from pip. This package is required for encrypting MCELF application images.
    pip install pyelftools construct
  By default, MCELF generation is OFF. User can enable/disable it with the macro MCELF_ENABLE=yes/no.
  i.e.: gmake -s dio_app MCELF_ENABLE=yes

========================= How to Build =========================================
- Open command prompt and go to $MCAL_INSTALL_DIR/build directory and type below

  gmake -s all

  This will and build all MCAL drivers as well as all MCAL
  examples

  gmake -s allclean

  This will clean all MCAL drivers as well as all MCAL
  examples

- TIP: Always use "-s" option with make to see user friendly prints
       during build.

- Optionally before build, edit the below in Rules.make file,
  depending on the kind of build you want to do:

  PLATFORM:=am263/am263px/am261
  PROFILE:=release/debug
  MCELF_ENABLE:=no/yes
  PACKAGE is applicable only for AM263Px
  PACKAGE:=SIP/C/R

  Valid values for are:
  am263     - AM263x
  am263px   - AM263px
  am261     - AM261x

  Valid values of PACKAGE for AM263Px are:
  SIP       - SIP package
  C         - Compatible package
  R         - Resolver package

  Valid values for PROFILE are:
  debug     - Debug build with NO compiler optimizations
              and symbolic debug info included
  release   - Release build with FULL compiler optimizations
              and symbolic debug info included

  Valid values for MCELF_ENABLE are:
  yes       - generation of MCELF format is enabled
  no        - generation of MCELF format is disabled

- The generated files are placed in the below folders,
  Executables   - $(DEST_ROOT)/<APP_NAME>/bin/$(PLATFORM)/<APP_NAME>_<CORE>_$(PROFILE).xer5f
  Libraries     - $(DEST_ROOT)/<MODULE_RELPATH>/lib/$(PLATFORM)/r5f/$(PROFILE)/*.aer5f
  Objects       - $(DEST_ROOT)/<MODULE_RELPATH>/obj/$(PLATFORM)/r5f/$(PROFILE)/*.oer5f
  Dependancies  - $(DEST_ROOT)/<APP_NAME>/obj/$(PLATFORM)/r5f/$(PROFILE)/.deps/*.P

- During development the below "gmake" targets can be also used be used for
  convenience:

  gmake -s examples         - incrementally builds MCAL drivers
                              and all examples

  gmake -s platforms        - incrementally builds for all supported PLATFORMs
  gmake -s profiles         - incrementally builds for all supported PROFILEs

  gmake -s all              - clean all and build all drivers, examples for default platform <am263>
  gmake -s allall           - incrementally builds for all supported PLATFORMs
                              AND PROFILEs

  gmake -s clean            - clean all drivers, examples
  gmake -s examples_clean   - clean all examples ONLY
  gmake -s platformsclean   - cleans for all supported PLATFORMs
  gmake -s profilesclean    - cleans for all supported PROFILEs
  gmake -s allclean         - cleans for all supported PLATFORMs AND PROFILEs

  gmake -s <examplename>    - incrementally builds MCAL drivers
                              and the specific example ONLY.

                              Values for <examplename> can be,
                              adc_app
                              can_app
                              cdd_cmpss_app
                              cdd_flc_app
                              dio_app
                              eth_app
                              fls_app
                              gpt_app
                              i2c_app
                              icu_app
                              ipc_notify_app
                              ipc_rpmsg_app
                              mcspi_app
                              mcu_app
                              port_app
                              pwm_app
                              uart_echo_dma_app
                              wdg_app

  gmake -s help             - Prints the help menu
