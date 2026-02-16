/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to
 * make, have made, use, import, offer to sell and sell ("Utilize") this software
 * subject to the terms herein. With respect to the foregoing patent license,
 * such license is granted solely to the extent that any such patent is necessary
 * to Utilize the software alone. The patent license shall not apply to any
 * combinations which include this software, other than combinations with devices
 * manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution.
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 * Any redistribution and use are licensed by TI for use only with TI Devices.
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 * Any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 * Any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
 * LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file     app_utils.h
 *
 *  \brief    This file contains common utility functions used by the MCAL apps
 *
 */

#ifndef APP_UTILS_H_
#define APP_UTILS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Std_Types.h"
#include "reg_sci.h"
#include "hw_ctrl_core.h"

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** brief Counter ID - 0U for Counter 32Khz */
#define APP_UTILS_CFG_COUNTER_ID ((CounterType)0x0U)
/** brief Counter frequency */
#define APP_UTILS_CFG_COUNTER_FREQ (32000U)

#define SYS_CLOCK_FREQ_XTAL 1200

#define SYS_CLOCK_FREQ_SYS_VCLK 48000000

/** \brief Magic String for App Test Status : Started */
#define APP_UTILS_TEST_STATUS_INIT (0x494E4954U)

/** \brief Magic String for App Test Status : PASS */
#define APP_UTILS_TEST_STATUS_PASS (0x50415353U)

/** \brief Magic String for App Test Status : FAIL */
#define APP_UTILS_TEST_STATUS_FAIL (0x46417376U)

/** \brief OCMC Address used to store App Test Status */
#define APP_UTILS_TEST_STATUS_ADDR (0x4033B100U)

/** @def pinMuxReg
 *   @brief  Register Frame Pointer
 *
 *   This pointer is used by the PinMux driver to access the pinmux module registers.
 */
#define pinMuxReg ((pinMuxBase_t *)0x53100000U)

/**
 * \brief Enum of Port Module Type used in module level pinmux enable
 */
typedef enum AppUtilsPinMux_ModuleType
{
    APPUTILS_PINMUX_MODULE_DCAN,    /*!< DCAN module */
    APPUTILS_PINMUX_MODULE_CANFD,   /*!< MCAN module */
    APPUTILS_PINMUX_MODULE_EPWM,    /*!< EPWM module */
    APPUTILS_PINMUX_MODULE_MIBSPI1, /*!< MIBSPI module */
    APPUTILS_PINMUX_MODULE_SPI2,    /*!< MIBSPI module */
    APPUTILS_PINMUX_MODULE_QSPI,    /*!< QSPImodule */
    APPUTILS_PINMUX_MODULE_GPIOA,   /*!< GPIOA module */
    APPUTILS_PINMUX_MODULE_GPIOB,   /*!< GPIOB module */
    APPUTILS_PINMUX_MODULE_NUM_MODULES
} AppUtilsPinMux_ModuleType;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct
{
    uint16                           NumModulesToEnable; /*!< Number of modules
                                                          * *where all pins of
                                                          * *module need to be
                                                          *enabled */
    const AppUtilsPinMux_ModuleType *ModuleEnable_pt;    /*!< Pointer to array
                                                          * *of modules to
                                                          * enable
                                                          **/
} AppUtilsPinMux_ConfigType;

/*! \brief
 * Software service task type
 */
typedef enum
{
    SVC_SWITCH_ARM_MODE = 0x0U,
    SVC_TEST_SWI        = 0x1U,
    NUM_OF_SVC_TYPES    = 0x2U
} SVC_TYPES;

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void AppUtils_defaultInit(void);
void AppUtils_sectionInit(void);
void AppUtils_defaultInitDiab(void);
void AppUtils_printf(const char *pStr, ...);

void UARTPrintf(const char *pcString, ...);

void Enable_Uart(void);

void   sys_cSwiInt(unsigned char svcNum);
uint32 AppUtils_getCurTimeInMsec(void);
uint32 AppUtils_getElapsedTimeInMsec(uint32 startTime);
void   AppUtils_delay(uint32 msec);
uint32 AppUtils_getStackUsage(void);
uint32 AppUtils_checkStackAndSectionCorruption(void);

void message(sciBASE_t *sci, const uint8 *str);

void           getCharacter(sciBASE_t *sci, uint8 *str, uint8 len);
char           AppUtils_getChar(void);
sint32         AppUtils_getNum(void);
sint32         app_utils_pinSelectFunc(uint32 pin, uint32 func);
void           app_utils_pinmuxUnlock(pinMuxBase_t *pinMuxRegp);
void           app_utils_pinmuxLock(pinMuxBase_t *pinMuxRegp);
Std_ReturnType AppUtilsPort_RefreshPortDrirection(void);
void           AppUtils_logTestResult(uint32 testResult);
Std_ReturnType AppUtilsPort_RefreshPortDrirection(void);
void           my_memcpy(void *dest, void *src, uint32 n);
void          *my_memset(void *s, int c, uint32 len);
void           AppUtils_SchM_Enter_EXCLUSIVE_AREA_0(void);
void           AppUtils_SchM_Exit_EXCLUSIVE_AREA_0(void);
void           AppUtils_sectionInit(void);
void           AppUtils_TimerInit();
void           AppUtils_TimerDeinit();
void           start_timer(void);
void           stop_timer(void);
uint32         Get_Ticks(void);
void           Det_Timeout(bool time_status);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef APP_UTILS_H_ */
