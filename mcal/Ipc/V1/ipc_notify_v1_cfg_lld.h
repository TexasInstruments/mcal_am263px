#include "mcal_hw_soc_baseaddress.h"

/* mailbox registers */
#define R5FSS0_0_MBOX_WRITE_DONE (MCAL_CSL_MSS_CTRL_U_BASE + 0x5FCU)
#define R5FSS0_0_MBOX_READ_REQ   (MCAL_CSL_MSS_CTRL_U_BASE + 0x600U)
#define R5FSS0_1_MBOX_WRITE_DONE (MCAL_CSL_MSS_CTRL_U_BASE + 0x608U)
#define R5FSS0_1_MBOX_READ_REQ   (MCAL_CSL_MSS_CTRL_U_BASE + 0x60CU)
#define C66SS0_MBOX_WRITE_DONE   (MCAL_CSL_DSS_CTRL_U_BASE + 0x56CU)
#define C66SS0_MBOX_READ_REQ     (MCAL_CSL_DSS_CTRL_U_BASE + 0x570U)

/* CPU bit positions within the mailbox registers */
#define R5FSS0_0_MBOX_PROC_BIT_POS (0U)
#define R5FSS0_1_MBOX_PROC_BIT_POS (4U)
#define C66SS0_MBOX_PROC_BIT_POS   (16U)

/* mailbox interrupts */
#define R5FSS0_0_MBOX_READ_REQ_INTR (77U)
#define R5FSS0_1_MBOX_READ_REQ_INTR (79U)
#define C66SS0_MBOX_READ_REQ_INTR   (94U)

/* dedicated mailbox memories address and size */
#define MSS_MBOX_MEM      (MCAL_CSL_MSS_MBOX_U_BASE)
#define MSS_MBOX_MEM_SIZE (8U * 1024U)
#define DSS_MBOX_MEM      (MCAL_CSL_DSS_MAILBOX_U_BASE)
#define DSS_MBOX_MEM_SIZE (4U * 1024U)

/* Interrupt config for R5FSS0-0 */
#define IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM (1U)
/* Interrupt config for R5FSS0-1 */
#define IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_1_NUM (1U)
/* Interrupt config for C66SS0 */
#define IPC_NOFTIY_INTERRUPT_CONFIG_C66SS0_NUM (1U)

/*
 * SW queue between each pair of CPUs
 *
 * place SW queues at the bottom of the dedicated mailbox memories.
 * Driver assume this memory is init to zero in bootloader as it's ECC protected and
 * needs to be intialized only once and to ensure that only one core has done the
 * mailbox ram initialization before ipc_init. If SBL is not used then Gel does the initialization.
 * We need 4*3 SW Q's for the 4x R5F to send messages to each other, i.e 384 B.
 *
 * Rest of the mailbox memory cna be used for ipc_rpmessage or custom message passing.
 */
#define C66SS0_TO_R5FSS0_0_SW_QUEUE \
    (IpcNotify_SwQueue*)(MSS_MBOX_MEM + MSS_MBOX_MEM_SIZE - (MAILBOX_MAX_SW_QUEUE_SIZE * 6U))
#define C66SS0_TO_R5FSS0_1_SW_QUEUE \
    (IpcNotify_SwQueue*)(MSS_MBOX_MEM + MSS_MBOX_MEM_SIZE - (MAILBOX_MAX_SW_QUEUE_SIZE * 5U))
#define R5FSS0_1_TO_R5FSS0_0_SW_QUEUE \
    (IpcNotify_SwQueue*)(MSS_MBOX_MEM + MSS_MBOX_MEM_SIZE - (MAILBOX_MAX_SW_QUEUE_SIZE * 4U))
#define R5FSS0_1_TO_C66SS0_SW_QUEUE \
    (IpcNotify_SwQueue*)(MSS_MBOX_MEM + MSS_MBOX_MEM_SIZE - (MAILBOX_MAX_SW_QUEUE_SIZE * 3U))
#define R5FSS0_0_TO_R5FSS0_1_SW_QUEUE \
    (IpcNotify_SwQueue*)(MSS_MBOX_MEM + MSS_MBOX_MEM_SIZE - (MAILBOX_MAX_SW_QUEUE_SIZE * 2U))
#define R5FSS0_0_TO_C66SS0_SW_QUEUE \
    (IpcNotify_SwQueue*)(MSS_MBOX_MEM + MSS_MBOX_MEM_SIZE - (MAILBOX_MAX_SW_QUEUE_SIZE * 1U))

IpcNotify_InterruptConfig* IpcNotifyCfg_getInterruptConfig(uint32 coreId);
uint32                     IpcNotifyCfg_getInterruptConfigNum(uint32 coreId);
IpcNotify_MailboxConfig*   IpcNotifyCfg_getMailboxConfig(uint32 selfCoreId, uint32 remoteCoreId);
