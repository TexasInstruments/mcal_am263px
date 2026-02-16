# Introduction

This is the release notes for MCAL AM26xx 11.02.00.06 done on 16-Feb-2026.
The MCAL package consists of MCAL Driver & Applications for AM26xx family of devices. The MCAL modules are compliant to AUTOSAR specification versioned **4.3.1**.

## Licensing
Refer to manifest file [mcal_manifest.html](./mcal_manifest.html) and [license.txt](./license.txt) present in installation base path

## Getting Started
The AM263x [HTML][am263x_user_guide_label] /AM263Px [HTML][am263px_user_guide_label] /AM261x [HTML][am261x_user_guide_label] User Guide provides the documentation and references necessary to begin development on TI's platforms using AM263x/AM263Px/AM261x.
This document details about supported driver, installation, dependencies, build instructions, steps to run example applications. This release package also includes module specific User Guides, test reports, configurator User Guide and memory footprint details.

## Dependencies

### Tools and Compilers
- Code Composer Studio: 20.4.0 or later
- TI ARM CLANG Compiler Version: 4.0.4
- Elektrobit Tresos Studio: 29.3 (EB\_Tresos\_ACG8.8.12\_Installer.zip). Please use link to request access to EB Tresos Studio and License: [Click Here][eb_tresos_download_label]

# What’s New

## New in this Release

<style>
  table, th, td {
    border: 1px solid black; /* Adds a 1px solid black border to the table, headers, and data cells */
    border-collapse: collapse; /* Collapses adjacent borders into a single line */
  }
</style>
<table>
  <thead>
    <tr>
      <th style="text-align: left;">Feature</th>
      <th style="text-align: left;">Module</th>
      <th style="text-align: left;">Supported Platforms</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>License changed to TI Text File License</td>
      <td>All</td>
      <td>MCAL license is changed from TI commercial to TI text file open source license.<br>
          All the license in the source code is changed to reflect this.<br>
          Note: Manifest update and publishing to Github is still pending.
      </td>
    </tr>
    <tr>
      <td>Added FSS Utility</td>
      <td>FSS</td>
      <td>AM263Px</td>
    </tr>
    <tr>
      <td>Bug Fixes</td>
      <td>All</td>
      <td>Please refer Fixed Defects section for more details.</td>
    </tr>
  </tbody>
</table>

## Compatibility

<table>
  <thead>
    <tr>
      <th style="text-align: left;">Module</th>
      <th style="text-align: left;">Compatibility Information</th>
      <th style="text-align: left;">Recommended/Expected Updates in Customer Application</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Common</td>
      <td>hal_stdtypes.h file and all macros defined in it are removed</td>
      <td>Application shall remove any usage of this header file and related macros. See description of defect MCAL-35744</td>
    </tr>
    <tr>
      <td>CDD PWM</td>
      <td>Channel parameter type changed from uint32 to Cdd_Pwm_ChannelType in multiple APIs</td>
      <td>Application shall use Cdd_Pwm_ChannelType for channel parameters instead of uint32. This is done as part of the MISRAC fixes</td>
    </tr>
  </tbody>
</table>

## Platform Specific Source Folder Information

Internal Files are organized in V0, V1, V2 and V3 folders. The below table lists the associated V0/V1/V2/V3 files to be used as per device.

```{eval-rst}
+------------+--------+---------+--------+
| Module     | AM263x | AM263Px | AM261x |
+------------+--------+---------+--------+
| ADC        | V0     | V0      | V0     |
| CAN        | V0     | V0      | V0     |
| CDD CMPSS  | am263  | am263px | am261  |
| CDD FLC    | NA     | am263px | am261  |
| CDD DMA    | V0     | V0      | V0     |
| CDD EPWM   | V0     | V0      | V0     |
| CDD I2C    | V0     | V0      | V0     |
| CDD IPC    | V0     | V0      | V2     |
| CDD UART   | V0     | V0      | V0     |
| DIO        | V0     | V0      | V0     |
| ETH        | V0     | V0      | V0     |
| ETHTRCV    | V0     | V0      | V0     |
| FLS        | V0     | V2      | V2     |
| FSIRX/TX   | V0     | V0      | V0     |
| GPT        | V0     | V0      | V0     |
| ICU        | V0     | V0      | V0     |
| LIN        | V0     | V0      | V0     |
| MCU        | V0     | V2      | V3     |
| PORT       | V0     | V0      | V0     |
| PWM        | V0     | V0      | V0     |
| SPI        | V0     | V0      | V0     |
| WDG        | V0     | V0      | V0     |
+------------+--------+---------+--------+
```

## Module Version

```{eval-rst}
+------------+----------+
| Module     | Version  |
+------------+----------+
| ADC        | 10.02.02 |
| CAN        | 10.02.02 |
| CDD_CMPSS  | 01.00.03 |
| CDD_FLC    | 01.00.03 |
| CDD_DMA    | 10.02.02 |
| CDD_FSIRX  | 10.02.02 |
| CDD_FSITX  | 10.02.02 |
| CDD_I2C    | 11.00.02 |
| CDD_IPC    | 10.02.02 |
| CDD_PWM    | 10.02.01 |
| CDD_UART   | 10.02.02 |
| DIO        | 10.02.02 |
| ETH        | 10.03.01 |
| ETHTRCV    | 10.04.00 |
| FLS        | 10.03.01 |
| GPT        | 10.02.02 |
| ICU        | 10.02.02 |
| LIN        | 10.03.01 |
| MCU        | 10.02.02 |
| PORT       | 10.02.03 |
| PWM        | 10.02.01 |
| SPI        | 10.02.02 |
| WDG        | 10.02.02 |
+------------+----------+
```

## Drivers Supported

<table>
  <thead>
    <tr>
      <th style="text-align: left;">Drivers</th>
      <th style="text-align: left;">Modules</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Micro controller Drivers</td>
      <td>GPT, WDG, MCU (with PWM XBAR, Output XBAR)</td>
    </tr>
    <tr>
      <td>Memory Driver</td>
      <td>FLS</td>
    </tr>
    <tr>
      <td>Communication Driver</td>
      <td>CAN, ETH, ETHTRCV, LIN, SPI</td>
    </tr>
    <tr>
      <td>I/O Drivers</td>
      <td>ADC, DIO, ICU, PORT, PWM</td>
    </tr>
    <tr>
      <td>CDD</td>
      <td>CMPSS, DMA, FLC, FSI, I2C, IPC, EPWM, UART</td>
    </tr>
  </tbody>
</table>

## Platforms Supported

```{eval-rst}
+---------+-----------------------------------+-------------------------+-------------+---------------+
|   SOC   |         Test Platform             | HOST (OS)               | Target (OS) | Supported CPU |
+---------+-----------------------------------+-------------------------+-------------+---------------+
| AM263x  | AM263x (am263x-cc)                | Build: Windows / Linux  | Baremetal   | R5F           |
+---------+-----------------------------------+ EB Configurator: Windows|             |               |
| AM263Px | AM263Px Control Card (am263px-cc) |                         |             |               |
|         +-----------------------------------+                         |             |               |
|         | AM263Px Launchpad (am263px-lp)    |                         |             |               |
|         +-----------------------------------+                         |             |               |
|         | AM263Px SIP Package (am263px-sip) |                         |             |               |
+---------+-----------------------------------+                         |             |               |
| AM261x  | AM261x (am261x-som)               |                         |             |               |
+---------+-----------------------------------+-------------------------+-------------+---------------+
```

# Fixed Defects

<table>
  <thead>
    <tr>
      <th style="text-align: left;">ID</th>
      <th style="text-align: left;">Summary</th>
      <th style="text-align: left;">Module</th>
      <th style="text-align: left;">Severity</th>
      <th style="text-align: left;">Applicable Platforms</th>
      <th style="text-align: left;">Description of Fix</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>MCAL-35744</td>
      <td>NULL_PTR implemented in hal_stdtypes.h</td>
      <td>Common</td>
      <td>Minor</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>NULL_PTR is removed from hal_stdtypes.h as it is available in Compiler.h file</td>
    </tr>
    <tr>
      <td>MCAL-35846</td>
      <td>Update all NULL usage to NULL_PTR</td>
      <td>Common</td>
      <td>Major</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>All usage of NULL is replaced with NULL_PTR which is defined in Compiler.h</td>
    </tr>
    <tr>
      <td>MCAL-35727</td>
      <td>BSWMD file fixes</td>
      <td>CDD I2C</td>
      <td>Minor</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>With fixes done in CDD I2C in previous releases, the BSWMD file was not updated.<br>
          Fixes include adding CddI2cMainFunctionPeriod configuration parameter, removing unavailable entries</td>
    </tr>
    <tr>
      <td>MCAL-35752</td>
      <td>Missing EXCLUSIVE_AREA in Cdd_Ipc_Bswmd.arxml</td>
      <td>CDD IPC</td>
      <td>Minor</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>Exclusive area is now added in Bswmd.arxml file</td>
    </tr>
    <tr>
      <td>MCAL-35748</td>
      <td>Missing quotation mark in BSW-MODULE-ENTRY UUID attribute</td>
      <td>CDD PWM</td>
      <td>Minor</td>
      <td>AM263Px</td>
      <td>See description</td>
    </tr>
    <tr>
      <td>MCAL-35749</td>
      <td>Mismatch AR-RELEASE-VERSION in Spi and Dio</td>
      <td>DIO, SPI</td>
      <td>Minor</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>AR-RELEASE-VERSION is fixed to 4.3.1</td>
    </tr>
    <tr>
      <td>MCAL-35750</td>
      <td>EthTrcv API implemented in the wrong header file</td>
      <td>ETHTRCV</td>
      <td>Minor</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>Datatypes like EthTrcv_BaudRateType should be part of AUTOSAR stubs.<br>
          Instead these were added in EthTrcv interface header files resulting in conflicts with standard AUTOSAR definitions.<br>
          These datatypes are not moved to the stubs.
      </td>
    </tr>
    <tr>
      <td>MCAL-35865</td>
      <td>Fls SFDP parameter structure should be in VAR section</td>
      <td>FLS</td>
      <td>Major</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>The Fls_Config_SFDP_1 structure in CFG files is writable and is now placed in SEC_VAR_INIT_UNSPECIFIED section</td>
    </tr>
    <tr>
      <td>MCAL-35747</td>
      <td>Extra closing tag FLS_bswmd.arxml</td>
      <td>FLS</td>
      <td>Minor</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>See description</td>
    </tr>
    <tr>
      <td>MCAL-35751</td>
      <td>CacheP.h is present as part of examples but not needed</td>
      <td>FLS</td>
      <td>Minor</td>
      <td>AM263Px, AM261x</td>
      <td>See description</td>
    </tr>
  </tbody>
</table>

# Open Defects

<table>
  <thead>
    <tr>
      <th style="text-align: left;">ID</th>
      <th style="text-align: left;">Summary</th>
      <th style="text-align: left;">Module</th>
      <th style="text-align: left;">Severity</th>
      <th style="text-align: left;">Applicable Platforms</th>
      <th style="text-align: left;">Workaround</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>MCAL-35346</td>
      <td>I2C: Cancel API is not functional</td>
      <td>CDD I2C</td>
      <td>Major</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>None. This will be fixed in future MCAL release</td>
    </tr>
    <tr>
      <td>MCAL-27007</td>
      <td>UART read/write with DMA enabled is not working</td>
      <td>CDD UART</td>
      <td>Minor</td>
      <td>AM261x</td>
      <td>Customer to use UART without DMA</td>
    </tr>
    <tr>
      <td>MCAL-34950</td>
      <td>Fls_Erase processed only in polling</td>
      <td>FLS</td>
      <td>Major</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>Fls_Erase can still be used. This will be further analysed</td>
    </tr>
    <tr>
      <td>MCAL-35392</td>
      <td>Boot and HSM Utils: Fix MISRAC and HIS Metric Violation</td>
      <td>Bootloader, Hsmclient</td>
      <td>Minor</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>This will be fixed in future MCAL release</td>
    </tr>
    <tr>
      <td>MCAL-25969</td>
      <td>Connecting Multiple Interrupt sources to single Interrupt Xbar line is not supported</td>
      <td>MCU</td>
      <td>Minor(Limitation)</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>Use single interrupt source to a XBar</td>
    </tr>
    <tr>
      <td>MCAL-13434</td>
      <td>DMA mode is not working with Cache Writeback enabled</td>
      <td>SPI</td>
      <td>Minor</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>Customer to use Cache Write through in case if they are using SPI+DMA</td>
    </tr>
  </tbody>
</table>

# Known Limitations

<table>
  <thead>
    <tr>
      <th style="text-align: left;">Summary</th>
      <th style="text-align: left;">Description</th>
      <th style="text-align: left;">Module</th>
      <th style="text-align: left;">Applicable Platforms</th>
      <th style="text-align: left;">Workaround</th>
      <th style="text-align: left;">Comments</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Unmapped memory sections with link time optimization</td>
      <td>
          With compiler link time optimization enabled, rodata like switch block lookup table goes to section like .rodata..Lswitch.table.Mcu_SystemInit.<br>
          This mapping cannot be controlled by section attributes.
      </td>
      <td>Memmap</td>
      <td>AM263x, AM263Px, AM261x</td>
      <td>NA</td>
      <td>This is a known compiler limitation</td>
    </tr>
    <tr>
      <td>ADC-R specific checks in configurator</td>
      <td>
          ADC-R instance in AM263Px supports only 4 channels (other instances supports 6 channels).<br>
          These checks are not performed in the EB configurator. User need to ensure they select the right configuration based on the AM263Px TRM
      </td>
      <td>ADC</td>
      <td>AM263Px</td>
      <td>NA</td>
      <td>NA</td>
    </tr>
  </tbody>
</table>

# Validation

Examples are validated with SBL Prebuilt binary of MCU+SDK available at ti.com.
For details refer test reports available in mcal_docs/csp/<platform> folder.

## Functional Safety Artifacts (CSP) Status

CSP - Compliance Support Package

<table>
  <thead>
    <tr>
      <th style="text-align: left;">Sr. No.</th>
      <th style="text-align: left;">Work Product</th>
      <th style="text-align: left;">Availability</th>
      <th style="text-align: left;">Where to Find Artifacts</th>
      <th style="text-align: left;">Comments</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>1</td>
      <td>Customer Docs: User Guide</td>
      <td>Yes</td>
      <td>Installer:mcal_docs\userguide\*platform*\index.html</td>
      <td>
          User Guide is present in installer as well as below TI software-dl locations
          <ol>
            <li>[AM263x Userguide][am263x_user_guide_label]</li>
            <li>[AM263Px Userguide][am263px_user_guide_label]</li>
            <li>[AM261x Userguide][am261x_user_guide_label]</li>
          </ol>
      </td>
    </tr>
    <tr>
      <td>2</td>
      <td>SW Manifest</td>
      <td>Yes</td>
      <td>Installer:mcal_manifest.html</td>
      <td>SW manifest is present in installer</td>
    </tr>
    <tr>
      <td>3</td>
      <td>
        Static Analysis Report
        <ol>
          <li>Static</li>
          <li>HIS</li>
          <li>MISRA-C</li>
        </ol>
      </td>
      <td>Yes</td>
      <td>Installer:mcal_docs\csp\*platform*\mcal_static_analysis_report.xlsx</td>
      <td>All MISRAC Mandatory & Critical warnings and errors are resolved. MISRAC Required and Advisory warnings and HIS metrics will be fixed in future releases</td>
    </tr>
    <tr>
      <td>4</td>
      <td>Test Reports: Test Cases and Test Results</td>
      <td>Yes</td>
      <td>Installer:mcal_docs\csp\*platform*\mcal_test_report.xlsx</td>
      <td>All test reports are present in installer.</td>
    </tr>
    <tr>
      <td>5</td>
      <td>
        Dynamic Analysis Report
        <ol>
          <li>MCDC</li>
          <li>Branch</li>
          <li>Region</li>
          <li>Line</li>
          <li>Function</li>
        </ol>
      </td>
      <td>No</td>
      <td>CSP</td>
      <td>Will be available in future releases. Please refer to device roadmap for details.</td>
    </tr>
    <tr>
      <td>6</td>
      <td>
        Bi-directional Traceability Report
        <ol>
          <li>MRD→SPS</li>
          <li>SPS→SW Arch →SW Design Doc→SW Units (Code)</li>
          <li>MRD→SPS→Test Case</li>
          <li>Test Case→Arch Test Case→Design</li>
        </ol>
      </td>
      <td>No</td>
      <td>CSP</td>
      <td>Will be available in future releases. Please refer to device roadmap for details.</td>
    </tr>
    <tr>
      <td>7</td>
      <td>SW FMEA</td>
      <td>No</td>
      <td>CSP</td>
      <td>Will be available in future releases. Please refer to device roadmap for details.</td>
    </tr>
    <tr>
      <td>8</td>
      <td>Detailed Design Document</td>
      <td>No</td>
      <td>CSP</td>
      <td>Will be available in future releases. Please refer to device roadmap for details.</td>
    </tr>
    <tr>
      <td>9</td>
      <td>Software Product Specification: List of functional, safety requirements for SW components</td>
      <td>No</td>
      <td>CSP</td>
      <td>Will be available in future releases. Please refer to device roadmap for details.</td>
    </tr>
    <tr>
      <td>10</td>
      <td>Architecture Document</td>
      <td>No</td>
      <td>CSP</td>
      <td>Will be available in future releases. Please refer to device roadmap for details.</td>
    </tr>
    <tr>
      <td>11</td>
      <td>SW Safety Manual</td>
      <td>No</td>
      <td>CSP</td>
      <td>Will be available in future releases. Please refer to device roadmap for details.</td>
    </tr>
    <tr>
      <td>12</td>
      <td>Safety Assessment</td>
      <td>No</td>
      <td>CSP</td>
      <td>Will be available in future releases. Please refer to device roadmap for details.</td>
    </tr>
  </tbody>
</table>

# Support

For technical support and additional assistance, visit E2E or contact local TI Field Application Engineer.

# Versioning
Each package version is composed of 4 period-delimited numbers - represented here by the letters M, m, p and b [MM.mm.pp.bb].
The table below provides a descriptive reference regarding package version numbering.

<table>
  <thead>
    <tr>
      <th style="text-align: left;">Digit</th>
      <th style="text-align: left;">Meaning</th>
      <th style="text-align: left;">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>MM</td>
      <td>Major revision</td>
      <td>Incremented when the new version is substantially different from the previous. For example, a new module added or an existing modules algorithm significantly altered</td>
    </tr>
    <tr>
      <td>mm</td>
      <td>Minor revision</td>
      <td>Incremented when the new version has changed but not in a major way. For example, some minor changes in the API or feature set or bug fixes. Reset to 00 for any change to MM revision</td>
    </tr>
    <tr>
      <td>pp</td>
      <td>Patch revision</td>
      <td>Incremented for patch/bug fix releases from any Major or Minor releases. Reset to 00 for any change to MM or mm revisions</td>
    </tr>
    <tr>
      <td>bb</td>
      <td>Build revision</td>
      <td>Incremented for each release delivery build. Reset to 01 for any change to MM, mm or pp revisions</td>
    </tr>
  </tbody>
</table>

TI is a global semiconductor design and manufacturing company. Innovate with 100,000+ analog ICs and embedded processors, along with software, tools and the industry‘s largest sales/support staff.
[© Copyright 1995-2025][copyright_label], Texas Instruments Incorporated. All rights reserved.

[Trademarks][trademark_label] | [Privacy Policy][policy_label] | [Terms of use][terms_use_label] | [Terms of sale][terms_sale_label]

[am263x_user_guide_label]:https://software-dl.ti.com/mcu-plus-sdk/esd/PLATFORM_SW_MCAL/AM263x/latest/index.html "AM263x User Guide"
[am263px_user_guide_label]:https://software-dl.ti.com/mcu-plus-sdk/esd/PLATFORM_SW_MCAL/AM263P/latest/index.html "AM263Px User Guide"
[am261x_user_guide_label]:https://software-dl.ti.com/mcu-plus-sdk/esd/PLATFORM_SW_MCAL/AM261x/latest/index.html "AM261x User Guide"
[eb_tresos_download_label]:https://www.ti.com/secureresources/PROCESSOR-SDK-MCAL-EB-TRESOS "EB Tresos Download"
[copyright_label]:https://www.ti.com/corp/docs/legal/copyright.shtml "TI Copyright"
[trademark_label]:https://www.ti.com/corp/docs/legal/trademark/trademrk.htm "Trademarks"
[policy_label]:https://www.ti.com/corp/docs/legal/privacy.shtml "Privacy Policy"
[terms_use_label]:https://www.ti.com/corp/docs/legal/termsofuse.shtml "Terms of use"
[terms_sale_label]:https://www.ti.com/lsds/ti/legal/termsofsale.page "Terms of sale"
