/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     Adc_Types.h
 *
 *  \brief    This file contains type definations of ADC MCAL driver
 *
 */

#ifndef ADC_TYPES_H_
#define ADC_TYPES_H_

/**
 * \addtogroup ADC Adc API GUIDE Header file
 * @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Std_Types.h"
#include "Adc_Cfg.h"
#include "Adc_Platform.h"

#if (STD_ON == ADC_DMA_MODE)
#include "Cdd_Dma.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \brief Number of MCAL channels - in terms of ADC HW, this represents the
 *  number of hardware steps.
 *  Note: In terms of ADC IP number of steps is 16.
 *        Due to AUTOSAR specification, the channel ID's should be unique i.e
 *        each channel Id and actual HW channel should have one to one mapping.
 *        So ADC_NUM_CHANNEL is fixed to 9 as number of actual HW channels
 *        available is also 9.
 *
 */
#define ADC_NUM_CHANNEL (6U)
/** \brief Minimum value of channel ID */
#define ADC_MIN_CHANNEL_ID (0U)
/** \brief Maximum value of channel ID */
#define ADC_MAX_CHANNEL_ID (ADC_NUM_CHANNEL - 1U)
/** \brief Numeric ID of an ADC channel */

/*
 *Design: MCAL-14594
 */
typedef uint8 Adc_ChannelType;

/** \brief Numeric ID of an ADC channel group */
/*
 * Design: MCAL-14595
 */
typedef uint8 Adc_GroupType;

/**
 * \brief Type for reading the converted values of a channel group (raw,
 *  without further scaling, right aligned).
 *
 *  Note: Even though the resolution for this ADC HW is 10-bit, we set this
 *  to 32-bit integer as the register read access is 32-bit.
 */
/*
 * Design: MCAL-14596
 */
typedef uint16 Adc_ValueGroupType;

/** \brief Type of clock prescaler factor. */
/*
 * Design: MCAL-14603
 */
typedef uint32 Adc_PrescaleType;

/**
 *  \brief Type of conversion time, i.e. the time during which the sampled
 *  analogue value is converted into digital representation.
 */
/*
 * Design: MCAL-14606
 */
typedef uint16 Adc_ConversionTimeType;

/**
 *  \brief Type of sampling time, i.e. the time during which the value is
 *  sampled (in clockcycles).
 */
/*
 * Design: MCAL-14610
 */
typedef uint16 Adc_SamplingTimeType;

/** \brief Type of channel resolution in number of bits. */
/*
 * Design: MCAL-14616
 */
typedef uint8 Adc_ResolutionType;

/** \brief Priority level of the channel. Lowest priority is 0. */
/*
 * Design: MCAL-14620
 */
typedef uint8 Adc_GroupPriorityType;

/** \brief Type of assignment of channels to a channel group. */
/*
 * Design: MCAL-14621
 */
typedef uint32 Adc_GroupDefType;

/**
 *  \brief Type for configuring the number of group conversions in streaming
 *   access mode (in single access mode, parameter is 1).
 */
/*
 * Design: MCAL-14622
 */
typedef uint16 Adc_StreamNumSampleType;

/** \brief Type for the value of the ADC module embedded timer. */
/*
 * Design: MCAL-14626
 */
typedef Adc_mcalTrigger_t Adc_HwTriggerTimerType;

/**
 *  \brief Specifies the identification (ID) for a ADC Hardware microcontroller
 *  peripheral (unit)
 */
typedef uint8 Adc_HWUnitType;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Typedef for group end notification function pointer */
typedef P2FUNC(void, ADC_APPL_CODE, Adc_GroupEndNotifyType)(void);

#if (STD_ON == ADC_DMA_MODE)
/** \brief Typedef for group end notification function pointer */
typedef Cdd_Edma_EventCallback Adc_DmaCallBackFunctionType;
#endif

/** \brief Current status of the conversion of the requested ADC Channel group */

/*
 * Design: MCAL-14617
 */
typedef enum
{
    /** \brief The conversion of the specified group has not been started.
     *   No result is available */
    ADC_IDLE,
    /** \brief The conversion of the specified group has been started and is still
     *   going on. So far no result is available */
    ADC_BUSY,
    /** \brief A conversion round (which is not the final one) of the specified group
     *  has been finished. A result is available for all channels of the
     *  group */
    ADC_COMPLETED,
    /** \brief The result buffer is completely filled. For each channel of the
     *   selected group the number of samples to be acquired is available */
    ADC_STREAM_COMPLETED
} Adc_StatusType;

/** \brief Type for configuring the trigger source for an ADC Channel group */

/*
 * Design: MCAL-14618
 */
typedef enum
{
    /** \brief Group is triggered by a software API call */
    ADC_TRIGG_SRC_SW,
    /** \brief Group is triggered by a hardware event
     *   Note: This feature is not supported in this driver */
    ADC_TRIGG_SRC_HW
} Adc_TriggerSourceType;

/** \brief Type for configuring the conversion mode of an ADC Channel group */

/*
 * Design: MCAL-14619
 */
typedef enum
{
    /** \brief Exactly one conversion of each channel in an ADC channel group is
     *   performed after the configured trigger event */
    ADC_CONV_MODE_ONESHOT,
    /** \brief Repeated conversions of each ADC channel in an ADC channel
     *   group are performed */
    ADC_CONV_MODE_CONTINUOUS
} Adc_GroupConvModeType;

/** \brief Type for configuring the streaming access mode buffer type */

/*
 * Design: MCAL-14623
 */
typedef enum
{
    /** \brief he ADC Driver stops the conversion as soon as the stream buffer
     *   is full (number of samples reached) */
    ADC_STREAM_BUFFER_LINEAR,
    /** \brief The ADC Driver continues the conversion even if the stream buffer is
     *   full (number of samples reached) by wrapping around the stream buffer
     *   itself */
    ADC_STREAM_BUFFER_CIRCULAR
} Adc_StreamBufferModeType;

/** \brief Type for configuring the access mode to group conversion results */

/*
 * Design: MCAL-14624
 */
typedef enum
{
    /** \brief Single value access mode */
    ADC_ACCESS_MODE_SINGLE,
    /** \brief Streaming access mode */
    ADC_ACCESS_MODE_STREAMING
} Adc_GroupAccessModeType;

/** \brief Type for configuring on which edge of the hardware trigger signal
 *  the driver should react, i.e. start the conversion.
 *
 *  Note: This feature is not supported in this driver
 */
/*
 * Design: MCAL-14625
 */
typedef enum
{
    /** \brief React on the rising edge of the hardware trigger signal */
    ADC_HW_TRIG_RISING_EDGE,
    /** \brief React on the falling edge of the hardware trigger signal */
    ADC_HW_TRIG_FALLING_EDGE,
    /** \brief React on both edges of the hardware trigger signal */
    ADC_HW_TRIG_BOTH_EDGES
} Adc_HwTriggerSignalType;

/** \brief Replacement mechanism, which is used on ADC group level, if a group
 *  conversion is interrupted by a group which has a higher priority.  */

/*
 * Design: MCAL-14628
 */
typedef enum
{
    /** \brief Abort/Restart mechanism is used on group level, if a group is
     *   interrupted by a higher priority group */
    ADC_GROUP_REPL_ABORT_RESTART,
    /** \brief Suspend/Resume mechanism is used on group level, if a group is
     *   interrupted by a higher priority group.
     *   Note: The implementation is same as abort/restart i.e. when a group
     *   is started again, previous intermediate results are discarded and
     *   the driver always starts from first channel of the group */
    ADC_GROUP_REPL_SUSPEND_RESUME,
} Adc_GroupReplacementType;

/** \brief In case of active limit checking: defines which conversion values
 *  are taken into account related to the boardes defined with
 *  AdcChannelLowLimit and AdcChannelHighLimit.
 *
 *  Note: This feature is not supported yet.
 */
/*
 * Design: MCAL-14629
 */
typedef enum
{
    /** \brief Range below low limit - low limit value included */
    ADC_RANGE_UNDER_LOW,
    /** \brief Range between low limit and high limit - high limit value included */
    ADC_RANGE_BETWEEN,
    /** \brief Range above high limit */
    ADC_RANGE_OVER_HIGH,
    /** \brief Complete range - independent from channel limit settings */
    ADC_RANGE_ALWAYS,
    /** \brief Range above low limit */
    ADC_RANGE_NOT_UNDER_LOW,
    /** \brief Range above high limit or below low limit - low limit value included */
    ADC_RANGE_NOT_BETWEEN,
    /** \brief Range below high limit - high limit value included */
    ADC_RANGE_NOT_OVER_HIGH
} Adc_ChannelRangeSelectType;

/** \brief Type of ADC Data access method.*/

typedef enum
{
    /** \brief Interrupt Provides the data.**/
    ADC_GROUP_INTERRUPT_ACCESS,
    /** \brief Polling method to get the data. */
    ADC_GROUP_POLLING_ACCESS,
    /** \brief DMA method to get the data. */
    ADC_GROUP_DMA_ACCESS
} Adc_GroupDataAccessType;

/** \brief Power state currently active or set as target power state.*/
/*
 * Design: MCAL-14631
 */
typedef enum
{
    /** \brief Full Power (0) */
    ADC_FULL_POWER,
    /** \brief Power modes with decreasing power consumptions */
    ADC_ZERO_POWER
} Adc_PowerStateType;

/** \brief Result of the requests related to power state transitions. */
/*
 * Design: MCAL-14634
 */
typedef enum
{
    /** \brief Power state change executed */
    ADC_SERVICE_ACCEPTED,
    /** \brief ADC Module not initialized */
    ADC_NOT_INIT,
    /** \brief Wrong API call sequence */
    ADC_SEQUENCE_ERROR,
    /** \brief The HW module has a failure which prevents it to enter the required
     *   power state */
    ADC_HW_FAILURE,
    /**\brief ADC Module does not support the requested power state */
    ADC_POWER_STATE_NOT_SUPP,
    /** \brief ADC Module cannot transition directly from the current power state
     *   to the requested power state or the HW peripheral is still busy */
    ADC_TRANS_NOT_POSSIBLE,
} Adc_PowerStateRequestResultType;

/** \brief Enum to number of samplings to average.
 *         ADC allows user to program the number of samplings to average.  */
typedef enum
{
    /** \brief Disable averaging */
    ADC_AVERAGING_MODE_NONE,
    /** \brief Set number of samplings to average to 2 */
    ADC_AVERAGING_MODE_2_SAMPLES,
    /** \brief Set number of samplings to average to 4 */
    ADC_AVERAGING_MODE_4_SAMPLES,
    /** \brief Set number of samplings to average to 8 */
    ADC_AVERAGING_MODE_8_SAMPLES,
    /** \brief Set number of samplings to average to 16 */
    ADC_AVERAGING_MODE_16_SAMPLES
} Adc_AveragingMode;

/**
 * \brief  Structure containing parameters for ADC MCAL channel configuration.
 *         In term of ADC hardware, this represents the step configuration.
 *         There are ADC_NUM_CHANNEL steps in the ADC hardware and each step
 *         could be mapped to an actual hardware input channel.
 */
typedef struct
{
    /** \brief The hardware channel number from which input is given.
     *   Valid values: ADC_MIN_HW_CHANNEL_ID to ADC_MAX_HW_CHANNEL_ID
     *   0x0 = Channel 1
     *   0x1 = Channel 2
     *   0x2 = Channel 3
     *   0x3 = Channel 4
     *   0x4 = Channel 5
     */
    uint32 hwChannelId;
    /** \brief The sampleWindow parameter is the acquisition window duration in SYSCLK cycles.
     *   It should be a value between 1 and 512 cycles inclusive.
     *   The selected duration must be at least as long as one ADCCLK cycle.
     *   Also, the datasheet will specify a minimum window duration requirement in nanoseconds.
     */
    uint32 samplewindow;
#if (STD_ON == ADC_ENABLE_LIMIT_CHECK)
    /** \brief The channel is enabled for limit check.
     */
    boolean channelEnableLimitCheck;
    /** \brief Sampled ADC data is compared to this value. If the sampled data is
     *   greater than this value, then interrupt is generated.
     *   Valid values: ADC_MIN_RANGE to ADC_MAX_RANGE.
     *
     *   This check can be enabled/disabled individually for each of the
     *   channel (step) using rangeCheckEnable parameter.
     */
    uint32  highRange;
    /** \brief Sampled ADC data is compared to this value. If the sampled data is
     *   lesser than this value, then interrupt is generated.
     *   Valid values: ADC_MIN_RANGE to ADC_MAX_RANGE.
     *
     *   This check can be enabled/disabled individually for each of the
     *   channel (step) using rangeCheckEnable parameter.
     */
    uint32  lowRange;
#endif
} Adc_ChannelConfigType;

/**
 *  \brief ADC Group configuration structure.
 */
/*
 *Design: MCAL-14593, MCAL-14832, MCAL-14837, MCAL-14838, MCAL-14839, MCAL-14840, MCAL-14842
 */
typedef struct
{
    /** \brief Group ID - This should be same as that of the index in to the
     *   groupCfg[] array */
    Adc_GroupType            groupId;
    /** \brief Group priority */
    Adc_GroupPriorityType    groupPriority;
    /** \brief HWUnit associated with this group */
    Adc_HWUnitType           hwUnitId;
    /** \brief Group end notification callback fxn pointer */
    Adc_GroupEndNotifyType   Adc_GroupEndNotification;
    /** \brief Contains how many samples fit into result buffer */
    Adc_StreamNumSampleType  streamNumSamples;
    /** \brief Group resolution - This is not configurable and should be set to
     *   ADC_DEF_CHANNEL_RESOLUTION */
    Adc_ResolutionType       resolution;
    /** \brief Operation mode of the group */
    Adc_GroupConvModeType    convMode;
    /** \brief Determines the trigger source (hw or sw trigger).
     *   Note: Only SW trigger is supported */
    Adc_TriggerSourceType    triggSrc;
    /** \brief Defines the type of the groups buffer */
    Adc_GroupAccessModeType  accessMode;
    /** \brief Use linear or circular stream buffer */
    Adc_StreamBufferModeType streamBufMode;
    /** \brief Use rising or falling edge for event pin trigger.
     *   Note: Since HW trigger is not supported, this parameter is not used */
    Adc_HwTriggerSignalType  hwTrigSignal;
    /** \brief Hardware trigger event.
     *   Note: Since HW trigger is not supported, this parameter is not used.
     *   Set it to 0. */
    Adc_HwTriggerTimerType   hwTrigTimer;
    /** \brief Group replacement logic when priority mechanism is ON - i.e
     *   prioritySupport is not ADC_PRIORITY_NONE. */
    Adc_GroupReplacementType groupReplacement;
    /** \brief Channels Enabled in Group. */
    uint16                   groupChannelMask;
#if (STD_ON == ADC_ENABLE_LIMIT_CHECK)
    /** \brief Group is supported for Limit check. */
    boolean grouplimitcheck;
#endif
    /** \brief Group Data Access method. */
    Adc_GroupDataAccessType groupDataAccessMode;
    /** \brief Group Data Access method. */
    uint32                  numChannels;
    /** \brief Number of channels in this group */
    uint32                  groupDmaChannelId;
    /** \brief Channel (HW step) configuration. numChannels elements should be
     *   initialized */
    Adc_ChannelConfigType   channelConfig[ADC_NUM_CHANNEL];
} Adc_GroupConfigType;

/**
 *  \brief ADC Hardware unit configuration structure.
 */
typedef struct
{
    /** \brief ADC HW unit ID */
    Adc_HWUnitType        hwUnitId;
    /** \brief ADC HW unit base addr */
    uint32                baseAddr;
    /** \brief ADC HW unit prescale*/
    Adc_mcalClkPrescale_t prescale;
    /** \brief ADC HW unit resolution*/
    Adc_mcalResolution_t  resolution;
} Adc_HwUnitConfigType;

#if (STD_ON == ADC_REGISTER_READBACK_API)
/**
 *  \brief ADC register readback structure
 *
 */
typedef struct
{
    /** \brief IP revision identifier */
    uint16 adcCtrl1;
    /** \brief Control Register */
    uint16 adcCtrl2;
} Adc_RegisterReadbackType;
#endif /* #if (STD_ON == ADC_REGISTER_READBACK_API) */

/**
 *  \brief ADC config structure
 */
typedef struct Adc_ConfigType_s
{
    /** \brief Maximum number of group
     *   Should not be more than ADC_MAX_GROUP */
    uint8                maxGroup;
    /** \brief Maximum number of HW unit
     *   Should not be more than ADC_MAX_HW_UNIT */
    uint8                maxHwUnit;
    /** \brief Group configurations */
    Adc_GroupConfigType  groupCfg[ADC_MAX_GROUP];
    /** \brief HW Unit configurations */
    Adc_HwUnitConfigType hwUnitCfg[ADC_MAX_HW_UNIT];
} Adc_ConfigType;

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef ADC_H_ */
