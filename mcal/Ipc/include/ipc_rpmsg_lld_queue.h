/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023-2024 Texas Instruments Incorporated
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

#ifndef IPC_RPMSG_QUEUE_H_
#define IPC_RPMSG_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

/* queue implementation using single linked list
 * no locks taken inside these APIs, locks should be
 * taken ouside as needed.
 */

struct RPMessage_QueueElem_s;

/* Q element structure, this MUST be the first field of a larger application
 * specific structure
 */
typedef struct RPMessage_QueueElem_s
{
    struct RPMessage_QueueElem_s *next; /* pointer to next element in list */

} RPMessage_QueueElem;

/* Q data structure, when Q is empty head and tail point to 0
 */
typedef struct RPMessage_Queue_s
{
    struct RPMessage_QueueElem_s *head; /* pointer to head of Q */
    struct RPMessage_QueueElem_s *tail; /* pointer to tail of Q */

} RPMessage_Queue;

/* reset Q data structure to empty state */
static inline void RPMessage_queueReset(RPMessage_Queue *q)
{
    q->head = 0;
    q->tail = 0;
}

/* add element into Q, adds to `tail` */
static inline void RPMessage_queuePut(RPMessage_Queue *q, RPMessage_QueueElem *elem)
{
    elem->next = 0;
    if (q->tail == 0)
    {
        /* Q is empty, head and tail point to new element */
        q->head = elem;
        q->tail = elem;
    }
    else
    {
        /* Q is not empty, add to tail */
        q->tail->next = elem;
        q->tail       = elem;
    }
}

/* get element from Q, extracts from `head` */
static inline RPMessage_QueueElem *RPMessage_queueGet(RPMessage_Queue *q)
{
    RPMessage_QueueElem *elem;

    if (q->head == 0)
    {
        /* Q is empty, return 0 */
        elem = 0;
    }
    else
    {
        /* Q is not empty, return head */
        elem = q->head;
        if (q->head == q->tail)
        {
            /* Q becomes empty due to extraction from head */
            q->head = 0;
            q->tail = 0;
        }
        else
        {
            /* Q is not empty due to extraction from head, move head to next element */
            q->head = q->head->next;
        }
        /* init next to 0 before returning */
        elem->next = 0;
    }
    return elem;
}

#ifdef __cplusplus
}
#endif

#endif /* IPC_RPMSG_QUEUE_H_ */
