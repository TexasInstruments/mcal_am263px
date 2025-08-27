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
 *  \file Spi_Utils.c
 *
 *  \brief Utility functions implementation file.
 *  This file defines the helper functions like create, add and remove nodes
 *
 */

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */
#include "string.h"
#include "Spi_Utils.h"

#ifdef __cplusplus
extern "C" {
#endif
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

static void Spi_utilsLinkDoublePri(Spi_UtilsLinkListObj *llobj, Spi_UtilsNode *node, const Spi_UtilsParams *params,
                                   uint8 currSeqId);
static void Spi_utilsUnLinkDoublePri(Spi_UtilsLinkListObj *llobj, Spi_UtilsNode *node);

/* ================================================================ */
/*                            Global Variables                      */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                          Function Definitions                    */
/* ================================================================ */
#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

void Spi_utilsInitLinkList(Spi_UtilsLinkListObj *llobj)
{
    /* Initialize the variables */
    llobj->headNode = (Spi_UtilsNode *)NULL_PTR;
    llobj->tailNode = (Spi_UtilsNode *)NULL_PTR;

    return;
}

void Spi_utilsDeInitLinkList(Spi_UtilsLinkListObj *llobj)
{
    llobj->headNode = (Spi_UtilsNode *)NULL_PTR;
    llobj->tailNode = (Spi_UtilsNode *)NULL_PTR;

    return;
}

void Spi_utilsLinkNodePri(Spi_UtilsLinkListObj *llobj, Spi_UtilsNode *node, const Spi_UtilsParams *params,
                          uint8 currSeqId)
{
    Spi_utilsLinkDoublePri(llobj, node, params, currSeqId);

    return;
}

void Spi_utilsUnLinkNodePri(Spi_UtilsLinkListObj *llobj, Spi_UtilsNode *node)
{
    Spi_utilsUnLinkDoublePri(llobj, node);

    return;
}

void Spi_utilsInitNodeObject(Spi_UtilsNode *node)
{
    node->next                    = (Spi_UtilsNode *)NULL_PTR;
    node->prev                    = (Spi_UtilsNode *)NULL_PTR;
    node->params.data             = NULL_PTR;
    node->params.priority         = 0U;
    node->params.seqId            = 0U;
    node->params.seqInterruptible = (uint8)FALSE;

    return;
}

Spi_UtilsNode *Spi_utilsGetHeadNode(const Spi_UtilsLinkListObj *llobj)
{
    return (llobj->headNode);
}

/**
 *  Spi_utilsLinkDoublePri
 *  \brief Links a node to a double link list based on priority.
 *  For nodes with same priority, the new node will be added to the
 *  last.
 */
static void Spi_utilsLinkDoublePri(Spi_UtilsLinkListObj *llobj, Spi_UtilsNode *node, const Spi_UtilsParams *params,
                                   uint8 currSeqId)
{
    uint32         interruptible = 0U;
    Spi_UtilsNode *curNode       = (Spi_UtilsNode *)NULL_PTR;
    Spi_UtilsNode *prevNode      = (Spi_UtilsNode *)NULL_PTR;

    prevNode                      = (Spi_UtilsNode *)NULL_PTR;
    node->params.data             = params->data;
    node->params.priority         = params->priority;
    node->params.seqId            = params->seqId;
    node->params.seqInterruptible = params->seqInterruptible;

    /* Add to the list based on priority */
    curNode = llobj->headNode;
    while (NULL_PTR != curNode)
    {
        /* Check if we can insert the job after current job */
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
 *  Spi_utilsUnLinkDoublePri
 *  \brief Unlinks a node from a double link list.
 */
static void Spi_utilsUnLinkDoublePri(Spi_UtilsLinkListObj *llobj, Spi_UtilsNode *node)
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
        llobj->tailNode = (Spi_UtilsNode *)NULL_PTR;
    }

    /* Reset node memory */
    node->next = (Spi_UtilsNode *)NULL_PTR;
    node->prev = (Spi_UtilsNode *)NULL_PTR;

    return;
}

#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"
#ifdef __cplusplus
}
#endif
