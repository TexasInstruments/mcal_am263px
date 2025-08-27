/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef MCAL_HW_SOC_IN_H_
#define MCAL_HW_SOC_IN_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "mcal_hw_soc_baseaddress.h"
#include "mcal_hw_soc_defines.h"

#define MCAL_CSL_MSS_CTRL_R5SS0_CORE0_MBOX_WRITE_DONE                          (0x00004000U)
#define MCAL_CSL_MSS_CTRL_R5SS0_CORE0_MBOX_READ_REQ                            (0x00004004U)
#define MCAL_CSL_MSS_CTRL_R5SS0_CORE0_MBOX_READ_DONE_ACK                       (0x00004008U)
#define MCAL_CSL_MSS_CTRL_R5SS0_CORE0_MBOX_READ_DONE                           (0x0000400CU)

#define MCAL_CSL_MSS_CTRL_R5SS0_CORE1_MBOX_WRITE_DONE                          (0x00008000U)
#define MCAL_CSL_MSS_CTRL_R5SS0_CORE1_MBOX_READ_REQ                            (0x00008004U)
#define MCAL_CSL_MSS_CTRL_R5SS0_CORE1_MBOX_READ_DONE_ACK                       (0x00008008U)
#define MCAL_CSL_MSS_CTRL_R5SS0_CORE1_MBOX_READ_DONE                           (0x0000800CU)


#ifdef __cplusplus
}
#endif
#endif /* CSLR_SOC_IN_H_ */
