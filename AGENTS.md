# AGENTS.md - MCAL Sitara MCU Project

## 1. Project Overview

This repository contains the **MCAL (Microcontroller Abstraction Layer)** drivers and applications for the **TI AM26xx family of devices** (AM263x, AM263Px, AM261x). The MCAL modules are compliant with **AUTOSAR specification version 4.3.1**.

### 1.1 Supported Platforms
- **AM263x** - AM263x Control Card (am263x-cc)
- **AM263Px** - AM263Px Control Card (am263px-cc), Launchpad (am263px-lp), SIP Package (am263px-sip)
- **AM261x** - AM261x SOM (am261x-som)

### 1.2 Target Architecture
- **CPU**: ARM Cortex-R5F
- **OS**: Baremetal
- **Build Environment**: Windows / Linux
- **Configurator**: EB Tresos Studio (Windows)

---

## 2. Directory Structure

```
mcal_sitara_mcu/
├── mcal/                    # MCAL driver source code
│   ├── Adc/                 # ADC driver
│   ├── Can/                 # CAN driver
│   ├── Cdd_Cmpss/           # CDD CMPSS driver
│   ├── Cdd_Flc/             # CDD FLC driver
│   ├── Dio/                 # DIO driver
│   ├── Dma/                 # DMA driver
│   ├── Epwm/                # EPWM driver
│   ├── Eth/                 # Ethernet driver
│   ├── EthTrcv/             # Ethernet Transceiver driver
│   ├── Fls/                 # Flash driver
│   ├── FsiRx/               # FSI Receive driver
│   ├── FsiTx/               # FSI Transmit driver
│   ├── Gpt/                 # GPT (Timer) driver
│   ├── I2c/                 # I2C driver
│   ├── Icu/                 # ICU driver
│   ├── Ipc/                 # IPC driver
│   ├── Lin/                 # LIN driver
│   ├── Mcal_Lib/            # MCAL common library
│   ├── Mcu/                 # MCU driver
│   ├── Port/                # Port driver
│   ├── Pwm/                 # PWM driver
│   ├── Spi/                 # SPI driver
│   ├── Uart/                # UART driver
│   ├── Wdg/                 # Watchdog driver
│   ├── autosar_include/     # AUTOSAR standard includes
│   ├── examples/            # Example applications
│   ├── examples_config/     # Example configurations
│   └── include/             # Common includes
├── mcal_config/             # EB tresos plugin files
├── mcal_docs/               # Documentation (CSP, user guides)
│   └── csp/                 # Compliance Support Package
├── mcal_misc/               # Miscellaneous utilities
│   ├── appimageGen/         # Application image generation
│   ├── ccs_test_automation/ # CCS test automation scripts
│   ├── MCAL_Automation/     # MCAL automation tools
│   └── scripts/             # Build and utility scripts
├── mcal_test/               # Unit tests for all modules
│   ├── adc_test/            # ADC unit tests
│   ├── can_test/            # CAN unit tests
│   ├── cmpss_test/          # CMPSS unit tests
│   ├── dio_test/            # DIO unit tests
│   ├── dma_test/            # DMA unit tests
│   ├── epwm_test/           # EPWM unit tests
│   ├── eth_test/            # Ethernet unit tests
│   ├── ethtrcv_test/        # Ethernet Transceiver unit tests
│   ├── flc_test/            # FLC unit tests
│   ├── fls_test/            # Flash unit tests
│   ├── fsi_test/            # FSI unit tests
│   ├── gpt_test/            # GPT unit tests
│   ├── i2c_test/            # I2C unit tests
│   ├── icu_test/            # ICU unit tests
│   ├── ipc_test/            # IPC unit tests
│   ├── lin_test/            # LIN unit tests
│   ├── mcu_test/            # MCU unit tests
│   ├── port_test/           # Port unit tests
│   ├── pwm_test/            # PWM unit tests
│   ├── spi_test/            # SPI unit tests
│   ├── uart_test/           # UART unit tests
│   ├── wdg_test/            # Watchdog unit tests
│   ├── common/              # Common test utilities
│   ├── coverage/            # Code coverage tools
│   ├── stf/                 # Simple Test Framework
│   ├── tools/               # Test tools
│   ├── Utils/               # Test utilities
│   └── ut_config/           # Unit test configurations
└── relnotes_archive/        # Release notes archive
```

---

## 3. MCAL Modules

### 3.1 Microcontroller Drivers
| Module | Description | Version |
|--------|-------------|---------|
| GPT | General Purpose Timer | 10.02.01 |
| WDG | Watchdog | 10.02.01 |
| MCU | Microcontroller Unit (with PWM XBAR, Output XBAR) | 10.02.01 |

### 3.2 Memory Drivers
| Module | Description | Version |
|--------|-------------|---------|
| FLS | Flash | 10.03.00 |

### 3.3 Communication Drivers
| Module | Description | Version |
|--------|-------------|---------|
| CAN | Controller Area Network | 10.02.01 |
| ETH | Ethernet | 10.03.00 |
| ETHTRCV | Ethernet Transceiver | 10.03.00 |
| LIN | Local Interconnect Network | 10.03.00 |
| SPI | Serial Peripheral Interface | 10.02.01 |

### 3.4 I/O Drivers
| Module | Description | Version |
|--------|-------------|---------|
| ADC | Analog to Digital Converter | 10.02.01 |
| DIO | Digital Input/Output | 10.02.01 |
| ICU | Input Capture Unit | 10.02.01 |
| PORT | Port | 10.02.02 |
| PWM | Pulse Width Modulation | 10.02.00 |

### 3.5 Complex Device Drivers (CDD)
| Module | Description | Version |
|--------|-------------|---------|
| CDD_CMPSS | Comparator Subsystem | 01.00.02 |
| CDD_DMA | Direct Memory Access | 10.02.01 |
| CDD_FLC | Flash Controller | 01.00.02 |
| CDD_FSIRX | Fast Serial Interface Receive | 10.02.01 |
| CDD_FSITX | Fast Serial Interface Transmit | 10.02.01 |
| CDD_I2C | Inter-Integrated Circuit | 11.00.01 |
| CDD_IPC | Inter-Processor Communication | 10.02.01 |
| CDD_PWM | Enhanced PWM | 10.02.00 |
| CDD_UART | Universal Asynchronous Receiver/Transmitter | 10.02.01 |

---

## 4. Build Instructions

### 4.1 Prerequisites
1. **Code Composer Studio**: 20.4.0 or later
2. **TI ARM CLANG Compiler**: Version 4.0.4
3. **EB Tresos Studio**: 29.3 (for configuration)
4. **gmake**: Included with CCS installation
5. **Python 3** with pip (for MCELF generation)
6. **OpenSSL v3** (for MCELF encryption)

### 4.2 Environment Setup
1. Edit `Rules.make` file:
   ```
   TOOLCHAIN_R5_VERSION=ti-cgt-armllvm_x.x.x.LTS
   CCS_PATH := C:/ti/ccsxxxx/ccs
   ```
2. Install Python dependencies:
   ```bash
   pip install pyelftools construct openpyxl
   ```

### 4.3 Build Commands
```bash
# Build all MCAL drivers and examples
gmake -s all

# Clean all
gmake -s allclean

# Build specific example
gmake -s <example_name>
# Examples: adc_app, can_app, dio_app, eth_app, fls_app, gpt_app,
#           i2c_app, icu_app, mcu_app, port_app, pwm_app, wdg_app, etc.

# Build for specific platform
gmake -s all PLATFORM=am263px

# Build with MCELF enabled
gmake -s dio_app MCELF_ENABLE=yes

# Show help
gmake -s help
```

### 4.4 Lint and Format Commands
```bash
# Run all lint checks (C/C++/headers and CMake files)
cd build/lint
gmake -s lint

# Lint only C/C++/header files
gmake -s lint_cxx

# Lint only CMake files
gmake -s lint_cmake

# Apply formatting to all source files
gmake -s format all

# Format only C/C++/header files
gmake -s format_cxx

# Format only CMake files
gmake -s format_cmake
```
**Note**: Lint uses `clang-format` for C/C++/headers and `cmakelang` for CMake files.

### 4.5 ARXML Generation Commands
```bash
# Generate ARXML files for all modules
cd build/arxml_gen
gmake -s all PLATFORM=am263px

# Supported platforms: AM263x, AM263Px, AM261x
```
**Description**: Converts `.xdm` configuration files to `.arxml` files for AUTOSAR configuration exchange.

### 4.6 AMDC (AUTOSAR Module Definition Checker) Commands
```bash
# Run AMDC validation for all modules
cd build/amdc
gmake -s all PLATFORM=am263px

# Clean AMDC output
gmake -s clean
```
**Description**: Validates ARXML files against AUTOSAR rules (A101-A223). Output logs are stored in `build/amdc/output/<PLATFORM>/`.

### 4.7 EB Tresos Commands
```bash
# Copy TI plugins to EB Tresos installation
cd build/ebtresos
gmake -s copy_plugins PLATFORM=am263px

# Delete TI plugins from EB Tresos installation
gmake -s delete_plugins

# Import and generate configuration for a project
gmake -s build_project EB_PROJECT_NAME=<project_name> EB_PROJECT_PATH=<path_to_project> PLATFORM=am263px

# For AM263Px with specific package type
gmake -s copy_plugins PLATFORM=am263px PACKAGE=C      # For C package
gmake -s copy_plugins PLATFORM=am263px PACKAGE=SIP    # For SIP package
```
**Key Variables**:
| Variable | Description |
|----------|-------------|
| EB_PROJECT_NAME | Name of the EB Tresos project |
| EB_PROJECT_PATH | Path to the project directory |
| EB_WORKSPACE | Workspace directory (default: `build/ebtresos/eb_workspace/<project_name>`) |
| PACKAGE | Package type for AM263Px: C, SIP, or R |

### 4.8 Build Configuration Options
| Variable | Values | Description |
|----------|--------|-------------|
| PLATFORM | am263, am263px, am261 | Target platform |
| PROFILE | debug, release | Build profile |
| MCELF_ENABLE | yes, no | Enable MCELF format generation |
| PACKAGE | SIP, C, R | Package type (AM263Px only) |

---

## 5. Utility Scripts

The `mcal_misc/scripts/` directory contains various utility scripts for build automation, release management, and validation.

### 5.1 Script Overview
| Script | Description |
|--------|-------------|
| `checksum.sh` | Generates MD5 checksums for source files (.c, .h, .xdm) per platform for release validation |
| `installer.sh` | Creates Windows and Linux installers for MCAL release packages using InstallBuilder |
| `mcal_kw_build.sh` | Runs Klocwork static analysis build for a single platform |
| `mcal_kw_build_all.sh` | Runs Klocwork static analysis build for all platforms (am263x, am263px, am261x) |
| `md_to_html.js` | Converts Markdown files to HTML using showdown.js library |
| `memmap_checker.py` | Validates memory section sizes in library files to ensure proper memory mapping |
| `release_tag.sh` | Tags AM26xx MCAL repositories with release version and pushes to origin |
| `run_libsize.sh` | Calculates and reports library sizes for all MCAL modules across platforms |
| `version_update.sh` | Updates version macros for all MCAL modules in source files and plugins |

### 5.2 memmap_checker.py - Memory Map Validator

**Purpose**: Parses section JSON files generated by `tiarmreadelf` and validates that standard sections (.text, .bss, .data, .rodata) have zero size in library files. This ensures proper memory section mapping in MCAL drivers.

**Usage**:
```bash
python memmap_checker.py -f <input_json_file>
```

**Parameters**:
- `-f, --file`: Input JSON file generated by tiarmreadelf containing section information

**Behavior**:
- Parses all files present in the library
- Checks standard sections: `.text`, `.bss`, `.data`, `.rodata`
- Reports error to stderr if any standard section has non-zero size
- Used to verify that MCAL library code is properly placed in custom memory sections

**Example**:
```bash
# Generate section JSON using tiarmreadelf
tiarmreadelf --sections --json mcal.aer5f > sections.json

# Validate memory sections
python memmap_checker.py -f sections.json
```

### 5.3 release_tag.sh - Release Tagging Script

**Purpose**: Automates the tagging of AM26xx MCAL repositories (mcal_sitara_mcu, mcal_docs, mcal_work_products) with consistent version tags and pushes them to the remote origin.

**Usage**:
```bash
./release_tag.sh --release_version="MM.mm.pp" [options]
```

**Required Parameters**:
- `--release_version`: Three-digit release version (e.g., "10.02.01")

**Optional Parameters**:
| Parameter | Description | Default |
|-----------|-------------|---------|
| `--tag_msg` | Custom tag message | Tag name |
| `--base_dir` | Base directory containing MCAL repos | `../../..` |
| `--mcal_ref` | mcal_sitara_mcu branch/reference | `next` |
| `--mcal_docs_ref` | mcal_docs branch/reference | `master` |
| `--mcal_wp_ref` | mcal_work_products branch/reference | `master` |
| `--tag_prefix` | Tag prefix | `REL.MCAL.AM26XX` |

**Tag Format**: `REL.MCAL.AM26XX.MM.mm.pp.bb`
- `MM.mm.pp`: Major.Minor.Patch version
- `bb`: Build number (auto-incremented based on existing tags)

**Example**:
```bash
# Tag release 10.02.01
./release_tag.sh --release_version="10.02.01"

# Tag with custom message and specific branch
./release_tag.sh --release_version="10.02.01" --tag_msg="Release 10.02.01" --mcal_ref="release_branch"
```

**Behavior**:
1. Fetches latest from origin
2. Finds the last build number for the given version
3. Auto-increments build number (two digits, e.g., 01, 02, ...)
4. Tags all three repositories at the specified references
5. Pushes tags to remote origin

---

## 6. Testing

### 6.1 Running Unit Tests
Each module has its own test directory under `mcal_test/`. Tests follow a consistent structure:
- `build/` - Build makefiles
- `testApp/` - Test application code
- `testInput/` - Test configuration and test cases
- `testLib/` - Test library and parser

### 6.2 Code Coverage
```bash
# Generate coverage for all modules
cd mcal_test
gmake -s -j8 coverage PLATFORM=am263px

# Generate coverage for specific module
gmake -s -j8 flc_coverage PLATFORM=am263px
```

Coverage reports are generated in: `mcal/binary/coverage_report/${PLATFORM}/`

---

## 7. Agent Guidelines

### 7.1 Code Style and Standards
- Follow **AUTOSAR 4.3.1** specification
- Comply with **MISRA-C** guidelines (Mandatory & Critical)
- Use consistent naming conventions as per AUTOSAR
- All code must pass static analysis

### 7.2 File Organization
- Driver source files: `mcal/<Module>/src/`
- Driver headers: `mcal/<Module>/include/`
- Platform-specific code: Organized in V0, V1, V2, V3 folders per platform
- Configuration files: Generated by EB Tresos configurator

### 7.3 Platform-Specific Source Mapping
| Module | AM263x | AM263Px | AM261x |
|--------|--------|---------|--------|
| ADC | V0 | V0 | V0 |
| CAN | V0 | V0 | V0 |
| CDD_IPC | V0 | V0 | V2 |
| FLS | V0 | V2 | V2 |
| MCU | V0 | V2 | V3 |
| Others | V0 | V0 | V0 |

### 7.4 Memory Sections
- Use appropriate memory section mappings as defined in `Memmap` headers
- For const sections, use `.rodata` instead of `.data` (CLANG convention)
- Refer to example linker command files for section organization

### 7.5 Testing Requirements
- All new features must have corresponding unit tests
- Tests should cover positive, negative, and boundary conditions
- Code coverage gaps must be documented with `TI_COVERAGE_GAP_START/STOP` comments

### 7.6 Documentation
- Update release notes for any changes
- Document API changes in user guides
- Maintain compatibility information for breaking changes

---

## 8. Key Files Reference

| File | Purpose |
|------|---------|
| `Rules.make` | Build configuration and paths |
| `mcal/mcal_component.mk` | MCAL component makefile |
| `mcal_test/makefile` | Main test makefile |
| `mcal_test/makefile_common.mk` | Common test build rules |
| `release_notes.md` | Current release notes |
| `mcal_manifest.html` | Software manifest |
| `license.txt` | License information |

---

## 9. Support and Resources

- **User Guides**:
  - [AM263x](https://software-dl.ti.com/mcu-plus-sdk/esd/PLATFORM_SW_MCAL/AM263x/latest/index.html)
  - [AM263Px](https://software-dl.ti.com/mcu-plus-sdk/esd/PLATFORM_SW_MCAL/AM263P/latest/index.html)
  - [AM261x](https://software-dl.ti.com/mcu-plus-sdk/esd/PLATFORM_SW_MCAL/AM261x/latest/index.html)
- **EB Tresos**: [Request Access](https://www.ti.com/secureresources/PROCESSOR-SDK-MCAL-EB-TRESOS)
- **Technical Support**: TI E2E Forums or local TI Field Application Engineer

---

## 10. Version Information

This AGENTS.md corresponds to MCAL AM26xx release with modules compliant to AUTOSAR 4.3.1.

© Copyright 1995-2025, Texas Instruments Incorporated. All rights reserved.