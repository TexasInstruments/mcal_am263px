/* ======================================================================
 *   Copyright (c) 2021 Texas Instruments Incorporated
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
 * \file  hw_types.h
 *
 * \brief This file contains the in-line functions required to read/write
 *        values from/to the hardware registers. This file also contains field
 *        manipulation macros to get and set field values.
 */

#ifndef HW_TYPES_H_
#define HW_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdio.h"
#include "Std_Types.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief   This macro reads a 32-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 32-bit value read from a register.
 */
#define HW_RD_REG32(addr)  HW_RD_REG32_RAW((uint32) (addr))

/**
 *  \brief   This macro writes a 32-bit value to a hardware register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   value   unsigned 32-bit value which has to be written to the
 *                   register.
 */
#define HW_WR_REG32(addr, value) \
    HW_WR_REG32_RAW((uint32) (addr), (uint32) (value))

/**
 *  \brief   This macro reads a 16-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 16-bit value read from a register.
 */
#define HW_RD_REG16(addr) (HW_RD_REG16_RAW((uint32) (addr)))

/**
 *  \brief   This macro writes a 16-bit value to a hardware register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   value   unsigned 16-bit value which has to be written to the
 *                   register.
 */
#define HW_WR_REG16(addr, value) \
    (HW_WR_REG16_RAW((uint32) (addr), (uint16) (value)))

/**
 *  \brief   This macro reads a 8-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 8-bit value read from a register.
 */
#define HW_RD_REG8(addr) (HW_RD_REG8_RAW((uint32) (addr)))

/**
 *  \brief   This macro writes a 8-bit value to a hardware
 *           register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   value   unsigned 8-bit value which has to be written to the
 *                   register.
 */
#define HW_WR_REG8(addr, value) \
    (HW_WR_REG8_RAW((uint32) (addr), (uint8) (value)))

/**
 *  \brief Macro to extract a field value. This macro extracts the field value
 *         from a 32-bit variable (which contains the register value).
 *         This macro does not read from actual register address, and only
 *         extracts the field from a variable.
 *
 *  \param regVal         32-bit variable containing the register value.
 *  \param REG_FIELD      Peripheral register bit field name, whose value has to
 *                        be extracted.
 */
#define HW_GET_FIELD(regVal, REG_FIELD) \
    (((regVal) & (uint32) REG_FIELD ## _MASK) >> (uint32) REG_FIELD ## _SHIFT)

/**
 *  \brief Macro to write a specific field value. This macro first clears the
 *         specified field value and then performs "OR" of the field value which
 *         is shifted and masked. This will set the field value at its
 *         desired position.
 *
 *  \param regVal         32-bit variable containing the register value.
 *  \param REG_FIELD      Peripheral register bit field name, to which specified
 *                        value has to be set.
 *  \param fieldVal       Value of the field which has to be set.
 */
#define HW_SET_FIELD32(regVal, REG_FIELD, fieldVal)                     \
    (regVal) = ((regVal) & (uint32) (~(uint32) REG_FIELD ## _MASK)) |   \
               ((((uint32) (fieldVal)) << (uint32) REG_FIELD ## _SHIFT) \
                & (uint32) REG_FIELD ## _MASK)

/**
 *  \brief Macro to write a specific field value. This macro first clears the
 *         specified field value and then performs "OR" of the field value which
 *         is shifted and masked. This will set the field value at its
 *         desired position.
 *
 *  \param regVal         16-bit variable containing the register value.
 *  \param REG_FIELD      Peripheral register bit field name, to which specified
 *                        value has to be set.
 *  \param fieldVal       Value of the field which has to be set.
 */
#define HW_SET_FIELD16(regVal, REG_FIELD, fieldVal)                        \
    (regVal) =                                                            \
         (((uint16) (regVal)) & (uint16) (~(uint16) REG_FIELD ## _MASK)) | \
         ((uint16)   (((uint16) (fieldVal)) <<                             \
                      (uint16) REG_FIELD ## _SHIFT)                        \
          & (uint16) REG_FIELD ## _MASK)

/**
 *  \brief Macro to write a specific field value. This macro first clears the
 *         specified field value and then performs "OR" of the field value which
 *         is shifted and masked. This will set the field value at its
 *         desired position.
 *
 *  \param regVal         8-bit variable containing the register value.
 *  \param REG_FIELD      Peripheral register bit field name, to which specified
 *                        value has to be set.
 *  \param fieldVal       Value of the field which has to be set.
 */
#define HW_SET_FIELD8(regVal, REG_FIELD, fieldVal)                     \
    (regVal) = ((regVal) & (uint8) (~(uint8) REG_FIELD ## _MASK)) |   \
                ((((uint8) (fieldVal)) << (uint8) REG_FIELD ## _SHIFT) \
                 & (uint8) REG_FIELD ## _MASK)

/**
 *  \brief This macro calls read-modify-write API for 32 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param regAddr        Register Address.
 *  \param REG_FIELD      Peripheral register bit field name, to which specified
 *                        value has to be set.
 *  \param fieldVal       Value of the field which has to be set.
 */
#define HW_WR_FIELD32(regAddr, REG_FIELD, fieldVal)                    \
    HW_WR_FIELD32_RAW((uint32) (regAddr), (uint32) REG_FIELD ## _MASK, \
                      (uint32) REG_FIELD ## _SHIFT, (uint32) (fieldVal))

/**
 *  \brief This macro calls read-modify-write API for 16 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param regAddr        Register Address.
 *  \param REG_FIELD      Peripheral register bit field name, to which specified
 *                        value has to be set.
 *  \param fieldVal       Value of the field which has to be set.
 */
#define HW_WR_FIELD16(regAddr, REG_FIELD, fieldVal)                     \
    (HW_WR_FIELD16_RAW((uint32) (regAddr), (uint16) REG_FIELD ## _MASK, \
                       (uint32) REG_FIELD ## _SHIFT, (uint16) (fieldVal)))

/**
 *  \brief This macro calls read-modify-write API for 8 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param regAddr        Register Address.
 *  \param REG_FIELD      Peripheral register bit field name, to which specified
 *                        value has to be set.
 *  \param fieldVal       Value of the field which has to be set.
 */
#define HW_WR_FIELD8(regAddr, REG_FIELD, fieldVal)                    \
    (HW_WR_FIELD8_RAW((uint32) (regAddr), (uint8) REG_FIELD ## _MASK, \
                      (uint32) REG_FIELD ## _SHIFT, (uint8) (fieldVal)))

/**
 *  \brief This macro calls read field API for 32 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param regAddr        Register Address.
 *  \param REG_FIELD      Peripheral register bit field name, from which
 *                        specified bit-field value has to be read.
 *  \return Value of the bit-field
 */
#define HW_RD_FIELD32(regAddr, REG_FIELD)                               \
    (HW_RD_FIELD32_RAW((uint32) (regAddr), (uint32) REG_FIELD ## _MASK, \
                       (uint32) REG_FIELD ## _SHIFT))

/**
 *  \brief This macro calls read field API for 16 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param regAddr        Register Address.
 *  \param REG_FIELD      Peripheral register bit field name, from which
 *                        specified bit-field value has to be read.
 *  \return Value of the bit-field
 */
#define HW_RD_FIELD16(regAddr, REG_FIELD)                               \
    (HW_RD_FIELD16_RAW((uint32) (regAddr), (uint16) REG_FIELD ## _MASK, \
                       (uint32) REG_FIELD ## _SHIFT))

/**
 *  \brief This macro calls read field API for 8 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param regAddr        Register Address.
 *  \param REG_FIELD      Peripheral register bit field name, from which
 *                        specified bit-field value has to be read.
 *  \return Value of the bit-field
 */
#define HW_RD_FIELD8(regAddr, REG_FIELD)                              \
    (HW_RD_FIELD8_RAW((uint32) (regAddr), (uint8) REG_FIELD ## _MASK, \
                      (uint32) REG_FIELD ## _SHIFT))

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Global Variables Declarations                        */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief   This function reads a 32-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 32-bit value read from a register.
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
uint32 HW_RD_REG32_RAW(uint32 addr);

/**
 *  \brief   This function writes a 32-bit value to a hardware register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   value   unsigned 32-bit value which has to be written to the
 *                   register.
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
void HW_WR_REG32_RAW(uint32 addr, uint32 value);

/**
 *  \brief   This function reads a 16-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 16-bit value read from a register.
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
uint16 HW_RD_REG16_RAW(uint32 addr);

/**
 *  \brief   This function writes a 16-bit value to a hardware register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   value   unsigned 16-bit value which has to be written to the
 *                   register.
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
void HW_WR_REG16_RAW(uint32 addr, uint16 value);

/**
 *  \brief   This function reads a 8-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 8-bit value read from a register.
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
uint8 HW_RD_REG8_RAW(uint32 addr);

/**
 *  \brief   This function writes a 8-bit value to a hardware
 *           register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   value   unsigned 8-bit value which has to be written to the
 *                   register.
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
void HW_WR_REG8_RAW(uint32 addr, uint8 value);

/**
 *  \brief   This function reads a 32 bit register, modifies specific set of
 *           bits and writes back to the register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   mask    Mask for the bit field.
 *  \param   shift   Bit field shift from LSB.
 *  \param   value   Value to be written to bit-field.
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
void HW_WR_FIELD32_RAW(uint32 addr,
                                     uint32 Mask,
                                     uint32 shift,
                                     uint32 value);

/**
 *  \brief   This function reads a 16 bit register, modifies specific set of
 *           bits and writes back to the register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   mask    Mask for the bit field.
 *  \param   shift   Bit field shift from LSB.
 *  \param   value   Value to be written to bit-field.
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
void HW_WR_FIELD16_RAW(uint32 addr,
                                     uint16 mask,
                                     uint32 shift,
                                     uint16 value);

/**
 *  \brief   This function reads a 8 bit register, modifies specific set of
 *           bits and writes back to the register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   mask    Mask for the bit field.
 *  \param   shift   Bit field shift from LSB.
 *  \param   value   Value to be written to bit-field.
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
void HW_WR_FIELD8_RAW(uint32 addr,
                                    uint8  mask,
                                    uint32 shift,
                                    uint8  value);

/**
 *  \brief   This function reads a 32 bit register, masks specific set of bits
 *           and the left shifted value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   mask    Mask for the bit field.
 *  \param   shift   Bit field shift from LSB.
 *
 *  \return  Bit-field value (absolute value - shifted to LSB position)
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
uint32 HW_RD_FIELD32_RAW(uint32 addr,
                                       uint32 mask,
                                       uint32 shift);

/**
 *  \brief   This function reads a 16 bit register, masks specific set of bits
 *           and the left shifted value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   mask    Mask for the bit field.
 *  \param   shift   Bit field shift from LSB.
 *
 *  \return  Bit-field value (absolute value - shifted to LSB position)
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
uint16 HW_RD_FIELD16_RAW(uint32 addr,
                                       uint16 mask,
                                       uint32 shift);

/**
 *  \brief   This function reads a 8 bit register, masks specific set of bits
 *           and the left shifted value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   mask    Mask for the bit field.
 *  \param   shift   Bit field shift from LSB.
 *
 *  \return  Bit-field value (absolute value - shifted to LSB position)
 */
#ifndef MCAL_DYNAMIC_BUILD
static inline
#endif
uint8 HW_RD_FIELD8_RAW(uint32 addr,
                                     uint8  mask,
                                     uint32 shift);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

#ifndef MCAL_DYNAMIC_BUILD
static inline uint32 HW_RD_REG32_RAW(uint32 addr)
{
    uint32 regVal = *(volatile uint32 *) addr;
    return (regVal);
}

static inline void HW_WR_REG32_RAW(uint32 addr, uint32 value)
{
    *(volatile uint32 *) addr = value;
    return;
}

static inline uint16 HW_RD_REG16_RAW(uint32 addr)
{
    uint16 regVal = *(volatile uint16 *) addr;
    return (regVal);
}

static inline void HW_WR_REG16_RAW(uint32 addr, uint16 value)
{
    *(volatile uint16 *) addr = value;
    return;
}

static inline uint8 HW_RD_REG8_RAW(uint32 addr)
{
    uint8 regVal = *(volatile uint8 *) addr;
    return (regVal);
}

static inline void HW_WR_REG8_RAW(uint32 addr, uint8 value)
{
    *(volatile uint8 *) addr = value;
    return;
}

static inline void HW_WR_FIELD32_RAW(uint32 addr,
                                     uint32 mask,
                                     uint32 shift,
                                     uint32 value)
{
    uint32 regVal = *(volatile uint32 *) addr;
    regVal &= (~mask);
    regVal |= (value << shift) & mask;
    *(volatile uint32 *) addr = regVal;
    return;
}

static inline void HW_WR_FIELD16_RAW(uint32 addr,
                                     uint16 mask,
                                     uint32 shift,
                                     uint16 value)
{
    uint32 tempVal;
    uint16 regVal = *(volatile uint16 *) addr;
    tempVal  = ((uint32) regVal);
    tempVal &= (~((uint32) mask));
    tempVal |= (((uint32) value) << shift) & ((uint32) mask);
    regVal   = (uint16) tempVal;
    *(volatile uint16 *) addr = regVal;
    return;
}

static inline void HW_WR_FIELD8_RAW(uint32 addr,
                                    uint8  mask,
                                    uint32 shift,
                                    uint8  value)
{
    uint32 tempVal;
    uint8  regVal = *(volatile uint8 *) addr;
    tempVal  = ((uint32) regVal);
    tempVal &= (~((uint32) mask));
    tempVal |= (((uint32) value) << shift) & ((uint32) mask);
    regVal   = (uint8) tempVal;
    *(volatile uint8 *) addr = regVal;
    return;
}

static inline uint32 HW_RD_FIELD32_RAW(uint32 addr,
                                       uint32 mask,
                                       uint32 shift)
{
    uint32 regVal = *(volatile uint32 *) addr;
    regVal = (regVal & mask) >> shift;
    return (regVal);
}

static inline uint16 HW_RD_FIELD16_RAW(uint32 addr,
                                       uint16 mask,
                                       uint32 shift)
{
    uint32 tempVal;
    uint16 regVal = *(volatile uint16 *) addr;
    tempVal = (((uint32) regVal & (uint32) mask) >> shift);
    regVal  = (uint16) tempVal;
    return (regVal);
}

static inline uint8 HW_RD_FIELD8_RAW(uint32 addr,
                                     uint8  mask,
                                     uint32 shift)
{
    uint32 tempVal;
    uint8  regVal = *(volatile uint8 *) addr;
    tempVal = (((uint32) regVal & (uint32) mask) >> shift);
    regVal  = (uint8) tempVal;
    return (regVal);
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef HW_TYPES_H_ */
