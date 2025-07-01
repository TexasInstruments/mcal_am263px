/*
 *
 * Copyright (C) 2022-2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file Adc_Utils.c
 *
 *  \brief Utility functions implementation file.
 *  This file defines the helper functions like create, add and remove nodes
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "string.h"
/*LDRA_ANALYSIS*/
#include "Adc.h"
#include "Adc_Priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void    Adc_utilsLinkDoublePri(Adc_UtilsLinkListObj *llobj, Adc_UtilsNode *node, void *data,
                                      Adc_GroupPriorityType priority, uint32 isPaused);
static void    Adc_utilsUnLinkDoublePri(Adc_UtilsLinkListObj *llobj, Adc_UtilsNode *node);
static boolean Adc_utilsFindLinkDoublePri(const Adc_UtilsLinkListObj *llobj, const Adc_UtilsNode *node);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define ADC_START_SEC_CODE
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

void Adc_utilsInitLinkList(Adc_UtilsLinkListObj *llobj)
{
    /* Initialize the variables */
    llobj->headNode = NULL;
    llobj->tailNode = NULL;

    return;
}

void Adc_utilsDeInitLinkList(Adc_UtilsLinkListObj *llobj)
{
    llobj->headNode = NULL;
    llobj->tailNode = NULL;

    return;
}

/*LDRA_INSPECTED 120 D 3 : MISRAC_2012_R.8.13 */
/* "Reason - assigned to a non const node object" */
void Adc_utilsLinkNodePri(Adc_UtilsLinkListObj *llobj, Adc_UtilsNode *node, void *data, Adc_GroupPriorityType priority,
                          uint32 isPaused)
{
    Adc_utilsLinkDoublePri(llobj, node, data, priority, isPaused);

    return;
}

void Adc_utilsUnLinkNodePri(Adc_UtilsLinkListObj *llobj, Adc_UtilsNode *node)
{
    Adc_utilsUnLinkDoublePri(llobj, node);

    return;
}

void Adc_utilsInitNodeObject(Adc_UtilsNode *node)
{
    node->next     = NULL;
    node->prev     = NULL;
    node->data     = NULL;
    node->priority = 0U;

    return;
}

Adc_UtilsNode *Adc_utilsGetHeadNode(const Adc_UtilsLinkListObj *llobj)
{
    return (llobj->headNode);
}

/**
 *  Adc_utilsLinkDoublePri
 *  \brief Links a node to a double link list based on priority.
 *  For nodes with same priority, the new node will be added to the last.
 */
/* Requirements : SWS_Adc_00312, SWS_Adc_00417 */
static void Adc_utilsLinkDoublePri(Adc_UtilsLinkListObj *llobj, Adc_UtilsNode *node, void *data,
                                   Adc_GroupPriorityType priority, uint32 isPaused)
{
    Adc_UtilsNode *curNode, *prevNode;

    node->data     = data;
    node->priority = priority;

    /*LDRA_INSPECTED 94 S : MISRAC_2012_R.11.1
     * "Reason - Pointer typecast required here to match
                  destination data type" */
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4
     * "Reason - Pointer typecast required here to match
                      destination data type" */
    prevNode = (Adc_UtilsNode *)NULL_PTR;
    /* Add to the list based on priority */
    curNode = llobj->headNode;
    while (NULL_PTR != curNode)
    {
        /* Condition 1: Nodes with the same priority are added to the bottom
         * of the existing nodes with same priority. So break only if
         * priority is high
         * Condition 2: Nodes with the same priority are added to the top
         * of the existing nodes with same priority. So break if
         * priority is high or same
         */
        if ((((uint32)FALSE == isPaused) && (priority > curNode->priority)) ||
            (((uint32)TRUE == isPaused) && (priority >= curNode->priority)))
        {
            break;
        }

        /* Move to next node */
        prevNode = curNode;
        curNode  = curNode->next;
    }

    /* Add the node between current and previous nodes */
    node->next = curNode;
    node->prev = prevNode;
    if (NULL_PTR != prevNode)
    {
        prevNode->next = node;
    }
    else
    {
        /* Adding to the top of the list */
        llobj->headNode = node;
    }

    if (NULL_PTR != curNode)
    {
        curNode->prev = node;
    }
    else
    {
        llobj->tailNode = node;
    }

    return;
}

/* Check if the node exists in the linked list or not */
/*LDRA_INSPECTED 120 D 1 : MISRAC_2012_R.8.13 */
/*LDRA_INSPECTED 120 D 2 : MISRAC_2012_R.8.13 */
/* "Reason - passed object is modified" */
static boolean Adc_utilsFindLinkDoublePri(const Adc_UtilsLinkListObj *llobj, const Adc_UtilsNode *node)
{
    Adc_UtilsNode *curNode;
    boolean        retVal = FALSE;

    curNode = llobj->headNode;
    while (NULL_PTR != curNode)
    {
        if (curNode == node)
        {
            retVal = TRUE;
            break;
        }
        curNode = curNode->next;
    }

    return retVal;
}

/**
 *  Adc_utilsUnLinkDoublePri
 *  \brief Unlinks a node from a double link list.
 */
static void Adc_utilsUnLinkDoublePri(Adc_UtilsLinkListObj *llobj, Adc_UtilsNode *node)
{
    boolean reVal;
    /*LDRA_INSPECTED 93 S : MISRAC_2012_R.11.1 */
    /* "Reason - Tool issue " */
    reVal = Adc_utilsFindLinkDoublePri(llobj, node);
    if (reVal == FALSE)
    {
        /* Node doesn't exist in the list */
    }
    else
    {
        if (NULL_PTR == node->prev)
        {
            /* Removing head node */
            llobj->headNode = node->next;
        }
        else
        {
            /* Removing non-head node */
            node->prev->next = node->next;
        }

        if (NULL_PTR != node->next)
        {
            node->next->prev = node->prev;
        }
        else
        {
            llobj->tailNode = node->prev;
        }

        /* Reset node memory */
        node->next = NULL;
        node->prev = NULL;
    }

    return;
}

#define ADC_STOP_SEC_CODE
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"
