/* ======================================================================
 *   Copyright (c) 2023-2024 Texas Instruments Incorporated
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
 *  \file Spi_Utils.h
 *
 *  \brief SPI utility functions header file
 *  This file declares the functions required to create, add and remove nodes.
 *
 */

#ifndef SPI_UTILS_H_
#define SPI_UTILS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**< \brief Typedef for Node structure. */
typedef struct Spi_UtilsNode_t Spi_UtilsNode;

/**
 *  struct Spi_UtilsParams
 *  \brief Structure for storing node info.
 */
typedef struct
{
    void  *data;
    /**< Node data pointer pointer */
    uint32 priority;
    /**< Priority of the node. Used for priority based linked list. Priority is
     *   in ascending order of the value. So 0 is the lowest priority and is
     *   added to the bottom of the node.Nodes with the same priority are always
     *   added to the bottom of the existing nodes with same priority. for
     *   non-priority based modes, this parameter is ignored and could be set
     *   to 0. */
    uint8  seqId;
    /**< Sequence ID to which the job belongs. */
    uint8  seqInterruptible;
    /**< Flag indicating whether the sequence to which this job belongs is
     *   interruptible or not. */
} Spi_UtilsParams;

/**
 *  struct Spi_UtilsNode_t
 *  \brief Self referential structure for double link list.
 */
struct Spi_UtilsNode_t
{
    Spi_UtilsNode  *next;
    /**< Pointer to the next node. */
    Spi_UtilsNode  *prev;
    /**< Pointer to the previous node. */
    Spi_UtilsParams params;
    /**< Node info structure. */
};

/**
 *  struct Spi_UtilsLinkListObj
 *  \brief Structure to the link list object information.
 */
typedef struct
{
    Spi_UtilsNode *headNode;
    /**< Head node reference pointer */
    Spi_UtilsNode *tailNode;
    /**< Tail node reference pointer */
} Spi_UtilsLinkListObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Init a link list object.
 *
 *  \param llobj            Link list object.
 */
void Spi_utilsInitLinkList(Spi_UtilsLinkListObj *llobj);

/**
 *  \brief De-init a link list object.
 *
 *  \param llobj            Link list object.
 */
void Spi_utilsDeInitLinkList(Spi_UtilsLinkListObj *llobj);

/**
 *  \brief Links a node to the linked list.
 *  The memory to the node object should be allocated by the caller. This
 *  is used for link list with priority.
 *
 *  \param llobj            Link list object.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to add to node.
 *  \param params           Pointer to node params containing info like data
 *                          pointer, priority, seqId, seqInterruptible.
 *  \param currSeqId        Current sequence ID in progress for the HW unit.
 *
 *  \Note
 */
void Spi_utilsLinkNodePri(Spi_UtilsLinkListObj *llobj, Spi_UtilsNode *node, const Spi_UtilsParams *params,
                          uint8 currSeqId);

/**
 *  \brief Unlinks the node from the list. Used for the priority link lists.
 *
 *  \param llobj            Link list object.
 *  \param node             Node pointer to be unlinked from the list.
 */
void Spi_utilsUnLinkNodePri(Spi_UtilsLinkListObj *llobj, Spi_UtilsNode *node);

/**
 *  \brief Initialize the node object with default value.
 *
 *  \param node             Node pointer to initialize.
 */
void Spi_utilsInitNodeObject(Spi_UtilsNode *node);

/**
 *  \brief                  Returns the reference to the head node. This does
 *                          not remove the node from the head.
 *
 *  \param llobj            Link list object.
 */
Spi_UtilsNode *Spi_utilsGetHeadNode(const Spi_UtilsLinkListObj *llobj);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SPI_UTILS_H_ */
