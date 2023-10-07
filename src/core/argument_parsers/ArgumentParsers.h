/**
 * @file ArgumentParsers.h
 *
 * This file contains declarations for parsing arguments of PDP-11 functions
 * within the PDP-11 emulator. In the PDP-11 architecture, function arguments
 * are stored immediately after the program in memory. These arguments represent
 * various data types and are accessed and utilized by PDP-11 instructions.
 * 
 * @date Created on 2021-09-15.
 * @author vsweatherfield
 */

#ifndef PDP11_EMULATOR_ARGUMENTPARSERS_H
#define PDP11_EMULATOR_ARGUMENTPARSERS_H

#include "types/ArgumentType.h"
#include "types/CommandType.h"
#include "types/ArgumentParserType.h"

#define UNUSED(x) (void)(x)

extern Arg ss, dd, nn, b, r, n;
extern char xx;

extern Arg_batch args[];

/**
 * @brief determines the addressing mode and the target register for the command
 * execution
 */
Arg do_register_mode(word w);

/**
 * @brief resets all the arguments to zeroes
 */
void reset_arguments();

void handle_nothing(Command cmd, word w);

/**
 * determines whether the command will be applied to a byte or a word,
 * depending on the first bit of the word w.
 * @param w - The machine word containing the command and its arguments.
 */
void handle_b_arg(Command cmd, word w);

/**
 * calculates the register to which the command will be applied based on
 * the last 3 bits of the command
 * @param w - The machine word containing the command and its arguments.
 */
Arg get_r(word w);

void handle_r_arg(Command cmd, word w);

/**
 * executes the given addressing mode specified by the argument ss, which is
 * represented by bits [5; 10] of the machine word w.
 * @param w - The machine word containing the command and its arguments.
 */
void handle_ss_arg(Command cmd, word w);

/**
 * executes the given addressing mode specified by the argument dd, which is
 * represented by bits [11; 16] of the machine word w.
 * @param cmd - command that is about to be applied
 * @param w - The machine word containing the command and its arguments.
 */
void handle_dd_arg(Command cmd, word w);

void handle_nn_arg(Command cmd, word w);

void handle_xx_arg(Command cmd, word w);

#endif  // PDP11_EMULATOR_ARGUMENTPARSERS_H
