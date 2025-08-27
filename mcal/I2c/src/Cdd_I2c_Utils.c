/* ======================================================================
 *   Copyright (C) 2023-2024 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file Cdd_I2c_Utils.c
 *
 *  \brief Utility functions implementation file.
 *  This file defines the helper functions like create, add and remove nodes
 *
 */

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */

#include "Cdd_I2c_Utils.h"

/* ================================================================ */
/*                           Macros & Typedefs                      */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                         Structure Declarations                   */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                          Function Declarations                   */
/* ================================================================ */

static void Cdd_I2c_UtilsLinkDoublePri(Cdd_I2c_UtilsLinkListObj *llobj, Cdd_I2c_UtilsNode *node,
                                       const Cdd_I2c_UtilsParams *params, uint8 currSeqId);
static void Cdd_I2c_UtilsUnLinkDoublePri(Cdd_I2c_UtilsLinkListObj *llobj, Cdd_I2c_UtilsNode *node);

/* ================================================================ */
/*                            Global Variables                      */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                          Function Definitions                    */
/* ================================================================ */

#define CDD_I2C_START_SEC_CODE
#include "Cdd_I2c_MemMap.h"

void Cdd_I2c_UtilsInitLinkList(Cdd_I2c_UtilsLinkListObj *llobj)
{
    /* Initialize the variables */
    llobj->headNode = (Cdd_I2c_UtilsNode *)NULL_PTR;
    llobj->tailNode = (Cdd_I2c_UtilsNode *)NULL_PTR;

    return;
}

void Cdd_I2c_UtilsDeInitLinkList(Cdd_I2c_UtilsLinkListObj *llobj)
{
    llobj->headNode = (Cdd_I2c_UtilsNode *)NULL_PTR;
    llobj->tailNode = (Cdd_I2c_UtilsNode *)NULL_PTR;

    return;
}

void Cdd_I2c_UtilsLinkNodePri(Cdd_I2c_UtilsLinkListObj *llobj, Cdd_I2c_UtilsNode *node,
                              const Cdd_I2c_UtilsParams *params, uint8 currSeqId)
{
    Cdd_I2c_UtilsLinkDoublePri(llobj, node, params, currSeqId);

    return;
}

void Cdd_I2c_UtilsUnLinkNodePri(Cdd_I2c_UtilsLinkListObj *llobj, Cdd_I2c_UtilsNode *node)
{
    Cdd_I2c_UtilsUnLinkDoublePri(llobj, node);

    return;
}

void Cdd_I2c_UtilsInitNodeObject(Cdd_I2c_UtilsNode *node)
{
    node->next                    = (Cdd_I2c_UtilsNode *)NULL_PTR;
    node->prev                    = (Cdd_I2c_UtilsNode *)NULL_PTR;
    node->params.data             = NULL_PTR;
    node->params.priority         = 0U;
    node->params.seqId            = 0U;
    node->params.seqInterruptible = (uint8)FALSE;

    return;
}

Cdd_I2c_UtilsNode *Cdd_I2c_UtilsGetHeadNode(const Cdd_I2c_UtilsLinkListObj *llobj)
{
    return (llobj->headNode);
}

/**
 *  Cdd_I2c_UtilsLinkDoublePri
 *  \brief Links a node to a double link list based on priority.
 *  For nodes with same priority, the new node will be added to the
 *  last.
 */
static void Cdd_I2c_UtilsLinkDoublePri(Cdd_I2c_UtilsLinkListObj *llobj, Cdd_I2c_UtilsNode *node,
                                       const Cdd_I2c_UtilsParams *params, uint8 currSeqId)
{
    uint32             interruptible = 0U;
    Cdd_I2c_UtilsNode *curNode       = (Cdd_I2c_UtilsNode *)NULL_PTR;
    Cdd_I2c_UtilsNode *prevNode      = (Cdd_I2c_UtilsNode *)NULL_PTR;

    prevNode                      = (Cdd_I2c_UtilsNode *)NULL_PTR;
    node->params.data             = params->data;
    node->params.priority         = params->priority;
    node->params.seqId            = params->seqId;
    node->params.seqInterruptible = params->seqInterruptible;

    /* Add to the list based on priority */
    curNode = llobj->headNode;
    while (NULL_PTR != curNode)
    {
        /* Check if we can insert the ch after current ch */
        interruptible = (uint32)TRUE;
        if ((((uint8)FALSE) == curNode->params.seqInterruptible) && (currSeqId == curNode->params.seqId))
        {
            interruptible = (uint32)FALSE;
        }

        /* Nodes with the same priority are always added to the bottom
         * of the existing nodes with same priority. So break only if
         * priority is high */
        if ((params->priority > curNode->params.priority) && (((uint32)TRUE) == interruptible))
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

/**
 *  Cdd_I2c_UtilsUnLinkDoublePri
 *  \brief Unlinks a node from a double link list.
 */
static void Cdd_I2c_UtilsUnLinkDoublePri(Cdd_I2c_UtilsLinkListObj *llobj, Cdd_I2c_UtilsNode *node)
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
        llobj->tailNode = (Cdd_I2c_UtilsNode *)NULL_PTR;
    }

    /* Reset node memory */
    node->next = (Cdd_I2c_UtilsNode *)NULL_PTR;
    node->prev = (Cdd_I2c_UtilsNode *)NULL_PTR;

    return;
}

#define CDD_I2C_STOP_SEC_CODE
#include "Cdd_I2c_MemMap.h"
