#define GPT_IRQ_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* Requirements : SWS_Gpt_00261 */

#include "Std_Types.h"
#include "Gpt.h"
#include "Gpt_Irq.h"

/* Common Design ID's */
/*
 *Design: MCAL-16437
 */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

#if ((GPT_IRQ_MAJOR_VERSION != (10U)) || (GPT_IRQ_MINOR_VERSION != (1U)))
#error "Version numbers of Gpt_Irq.c and Gpt_Irq.h are inconsistent!"
#endif

#define GPT_START_SEC_ISR_CODE
/*LDRA_INSPECTED 243 S : MISRAC_2012_D.4.10
 * "Reason - Memmap file cannot have include guard w.r.o autosar spec " */
#include "Gpt_MemMap.h"
#if defined(GPT_CHANNEL_0)
/**********************************************************************************************************************
    Function name:  Gpt_Ch0Isr
    Description: The Channel0 Interrupt Subroutine calls Notification function depending on the
channel mode. If Gpt_IsrIndex[0] = GPT_CH_MODE_CONTINUOUS, the Function called is Gpt_NotifContIsr
    If Gpt_IsrIndex[0] = GPT_CH_MODE_ONESHOT, the Function called is Gpt_NotifSingleIsr
    If Gpt_IsrIndex[0] = GPT_CH_MODE_CONT_WAKEUP, the Function called is Gpt_WakeupContIsr
    If Gpt_IsrIndex[0] = GPT_CH_MODE_ONESHOT_WAKEUP, the Function called is Gpt_WakeupSingleIsr
**********************************************************************************************************************/
/*LDRA_INSPECTED 76 D : MISRAC_2012_R.2.1
 * "Reason - ISR is registered in application and called by dispatcher" */
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch0Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch0Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[0U]](0U);
}
#endif
#if defined(GPT_CHANNEL_1)
/**********************************************************************************************************************
   Function name:  Gpt_Ch1Isr
   Description: The Channel1 Interrupt Subroutine calls Notification function depending on the
 channel mode. If Gpt_IsrIndex[1] = GPT_CH_MODE_CONTINUOUS, the Function called is Gpt_NotifContIsr
    If Gpt_IsrIndex[1] = GPT_CH_MODE_ONESHOT, the Function called is Gpt_NotifSingleIsr
    If Gpt_IsrIndex[1] = GPT_CH_MODE_CONT_WAKEUP, the Function called is Gpt_WakeupContIsr
    If Gpt_IsrIndex[1] = GPT_CH_MODE_ONESHOT_WAKEUP, the Function called is Gpt_WakeupSingleIsr
 **********************************************************************************************************************/
/*LDRA_INSPECTED 76 D : MISRAC_2012_R.2.1
 * "Reason - ISR is registered in application and called by dispatcher" */
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch1Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch1Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[1U]](1U);
}
#endif
#if defined(GPT_CHANNEL_2)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch2Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch2Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[2U]](2U);
}
#endif
#if defined(GPT_CHANNEL_3)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch3Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch3Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[3U]](3U);
}
#endif
#if defined(GPT_CHANNEL_4)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch4Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch4Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[4U]](4U);
}
#endif
#if defined(GPT_CHANNEL_5)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch5Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch5Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[5U]](5U);
}
#endif
#if defined(GPT_CHANNEL_6)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch6Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch6Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[6U]](6U);
}
#endif
#if defined(GPT_CHANNEL_7)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch7Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch7Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[7U]](7U);
}
#endif
#if defined(GPT_CHANNEL_8)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch8Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch8Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[8U]](8U);
}
#endif
#if defined(GPT_CHANNEL_9)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch9Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch9Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[9U]](9U);
}
#endif
#if defined(GPT_CHANNEL_10)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch10Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch10Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[10U]](10U);
}
#endif
#if defined(GPT_CHANNEL_11)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch11Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch11Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[11U]](11U);
}
#endif
#if defined(GPT_CHANNEL_12)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch12Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch12Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[12U]](12U);
}
#endif
#if defined(GPT_CHANNEL_13)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch13Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch13Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[13U]](13U);
}
#endif
#if defined(GPT_CHANNEL_14)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch14Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch14Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[14U]](14U);
}
#endif
#if defined(GPT_CHANNEL_15)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch15Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch15Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[15U]](15U);
}
#endif

#if defined(GPT_CHANNEL_16)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch16Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch16Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[16U]](16U);
}
#endif

#if defined(GPT_CHANNEL_17)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch17Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch17Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[17U]](17U);
}
#endif

#if defined(GPT_CHANNEL_18)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch18Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch18Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[18U]](18U);
}
#endif

#if defined(GPT_CHANNEL_19)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch19Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch19Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[19U]](19U);
}
#endif

#if defined(GPT_CHANNEL_20)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch20Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch20Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[20U]](20U);
}
#endif

#if defined(GPT_CHANNEL_21)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch21Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch21Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[21U]](21U);
}
#endif

#if defined(GPT_CHANNEL_22)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch22Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch22Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[22U]](22U);
}
#endif

#if defined(GPT_CHANNEL_23)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch23Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch23Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[23U]](23U);
}
#endif

#if defined(GPT_CHANNEL_24)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch24Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch24Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[24U]](24U);
}
#endif

#if defined(GPT_CHANNEL_25)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch25Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch25Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[25U]](25U);
}
#endif

#if defined(GPT_CHANNEL_26)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch26Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch26Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[26U]](26U);
}
#endif

#if defined(GPT_CHANNEL_27)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch27Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch27Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[27U]](27U);
}
#endif

#if defined(GPT_CHANNEL_28)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch28Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch28Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[28U]](28U);
}
#endif

#if defined(GPT_CHANNEL_29)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch29Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch29Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[29U]](29U);
}
#endif

#if defined(GPT_CHANNEL_30)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch30Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch30Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[30U]](30U);
}
#endif

#if defined(GPT_CHANNEL_31)
MCAL_INTERRUPT_ATTRIBUTE
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
void Gpt_Ch31Isr(void)
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch31Isr)
#endif
{
    Gpt_IsrNotifyFunctions[Gpt_IsrIndex[31U]](31U);
}
#endif

/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#define GPT_STOP_SEC_ISR_CODE
#include "Gpt_MemMap.h"
