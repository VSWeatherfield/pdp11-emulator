/**
 * @file AddressingModes.h
 *
 * This file contains declarations for addressing modes utilized in the
 * PDP-11 emulator. Addressing modes define various methods for accessing
 * and referencing data in memory during instruction execution in the
 * PDP-11 architecture.
 *
 * @date Created on 2021-09-15.
 * @author vsweatherfield
 */


#ifndef PDP11_EMULATOR_ADDRESSINGMODES_H
#define PDP11_EMULATOR_ADDRESSINGMODES_H

#include "types/ArgumentType.h"
#include "types/ModeType.h"

#define UNUSED(x) (void)(x)

extern Mode modes[];

/**
 * @brief pdp11 r assembler command   (register)
 * @param rgstr register number whose contents are being accessed
 * @param res result storage after accessing the given register using the given
 * addressing mode
 */
void do_mode_0(Arg* res, word rgstr);

/**
 * @brief pdp11 (r) or @r assembler command   (register deferred)
 * @param rgstr register number whose contents are being accessed
 * @param res result storage after accessing the given register using the given
 * addressing mode
 */
void do_mode_1(Arg* res, word rgstr);

/**
 * @brief pdp11 (r)+ or #nn assembler command   (auto-increment) or (immediate)
 * respectiverly
 * @param rgstr register number whose contents are being accessed
 * @param res result storage after accessing the given register using the given
 * addressing mode
 * @warning when the address is out of bounds, the program may not stop
 */
void do_mode_2(Arg* res, word rgstr);

/**
 * @brief pdp11 @(r)+ or @#nn assembler command   (auto-increment deferred) or
 * (absolute) respectively
 * @param rgstr register number whose contents are being accessed
 * @param res result storage after accessing the given register using the given
 * addressing mode
 * @warning when the address is out of bounds, the program may not stop
 */
void do_mode_3(Arg* res, word rgstr);

/**
 * @brief pdp11 –(r) assembler command   (auto-decrement)
 * @param rgstr register number whose contents are being accessed
 * @param res result storage after accessing the given register using the given
 * addressing mode
 */
void do_mode_4(Arg* res, word rgstr);

/**
 * @brief pdp11  @–(r) assembler command   (auto-decrement deferred)
 * @param rgstr register number whose contents are being accessed
 * @param res result storage after accessing the given register using the given
 * addressing mode
 * @warning when the address is out of bounds, the program may not stop
 */
void do_mode_5(Arg* res, word rgstr);

/**
 * @brief pdp11 nn or nn(r) assembler command   (index) or (relative)
 * respectively
 * @param rgstr register number whose contents are being accessed
 * @param res result storage after accessing the given register using the given
 * addressing mode
 */
void do_mode_6(Arg* res, word rgstr);

/**
 * @brief pdp11 @nn(r) or @nn assembler command   (index deferred) or (relative
 * deffered) respectively
 * @param rgstr the register whose contents are being accessed
 * @param res result storage after accessing the given register using the given
 * addressing mode
 */
void do_mode_7(Arg* res, word rgstr);

void do_unknown_mode(Arg* res, word rgstr);

#endif  // PDP11_EMULATOR_ADDRESSINGMODES_H
