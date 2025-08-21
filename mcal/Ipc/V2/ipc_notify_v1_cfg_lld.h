#include "mcal_hw_soc.h"
#include "mcal_hw_soc_baseaddress.h"

/* mailbox registers */
#define R5FSS0_0_MBOX_WRITE_DONE (MCAL_CSL_MSS_CTRL_U_BASE + MCAL_CSL_MSS_CTRL_R5SS0_CORE0_MBOX_WRITE_DONE)
#define R5FSS0_0_MBOX_READ_REQ   (MCAL_CSL_MSS_CTRL_U_BASE + MCAL_CSL_MSS_CTRL_R5SS0_CORE0_MBOX_READ_REQ)
#define R5FSS0_1_MBOX_WRITE_DONE (MCAL_CSL_MSS_CTRL_U_BASE + MCAL_CSL_MSS_CTRL_R5SS0_CORE1_MBOX_WRITE_DONE)
#define R5FSS0_1_MBOX_READ_REQ   (MCAL_CSL_MSS_CTRL_U_BASE + MCAL_CSL_MSS_CTRL_R5SS0_CORE1_MBOX_READ_REQ)

/* CPU bit positions within the mailbox registers */
#define R5FSS0_0_MBOX_PROC_BIT_POS (0U)
#define R5FSS0_1_MBOX_PROC_BIT_POS (4U)

/* mailbox interrupts */
#define R5FSS0_0_MBOX_READ_REQ_INTR (158U)
#define R5FSS0_1_MBOX_READ_REQ_INTR (158U)

/* A delay of 60-70 clock cycle is recommended before clear pending read request from remote core
 * This delay is implemented as a loop
 */
#define IPC_NOTIFY_WAIT_CYCLES (5U)

/* A counter that restricts the loop to pend in isr forever and also avoid any race around condtion between the cores */
#define IPC_NOTIFY_LOOP_COUNTER_MAX (1000U)
/* dedicated mailbox memories address and size */
#define MSS_MBOX_MEM      (MCAL_CSL_MBOX_SRAM_U_BASE)
#define MSS_MBOX_MEM_SIZE (16U * 1024U)

/*
 * SW queue between each pair of CPUs
 *
 * place SW queues at the bottom of the dedicated mailbox memories.
 * Driver assume this memory is init to zero in bootloader as it's ECC protected and
 * needs to be intialized only once and to ensure that only one core has done the
 * mailbox ram initialization before ipc_init. If SBL is not used then Gel does the initialization.
 * We need 2*1 SW Q's for the 2x R5F to send messages to each other.
 *
 * Rest of the mailbox memory cna be used for ipc_rpmessage or custom message passing.
 */
#define R5FSS0_0_TO_R5FSS0_1_SW_QUEUE \
    (IpcNotify_SwQueue*)(MSS_MBOX_MEM + MSS_MBOX_MEM_SIZE - (MAILBOX_MAX_SW_QUEUE_SIZE * 2U))
#define R5FSS0_1_TO_R5FSS0_0_SW_QUEUE \
    (IpcNotify_SwQueue*)(MSS_MBOX_MEM + MSS_MBOX_MEM_SIZE - (MAILBOX_MAX_SW_QUEUE_SIZE * 1U))

#define IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_1_NUM (1U)
#define IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM (1U)

IpcNotify_InterruptConfig* IpcNotifyCfg_getInterruptConfig(uint32 coreId);
uint32                     IpcNotifyCfg_getInterruptConfigNum(uint32 coreId);
IpcNotify_MailboxConfig*   IpcNotifyCfg_getMailboxConfig(uint32 selfCoreId, uint32 remoteCoreId);
sint32 IpcNotify_trigInterrupt(uint32 selfCoreId, uint32 remoteCoreId, uint32 mailboxBaseAddr, uint32 intrBitPos);
void   IpcNotify_wait(void);
