/**
 * @file Commands.h
 *
 * This file contains declarations for PDP-11 functions and their associated
 * operations within the PDP-11 emulator. These functions include operations
 * such as data movement (e.g., MOV, MOVB), arithmetic operations (e.g., ADD,
 * INC), control flow (e.g., JMP, JSR), and flag manipulation (e.g., TST, CMP).
 * Each function is responsible for carrying out its designated operation on
 * the PDP-11 processor's data and control flow.
 *
 * @date Created on 2021-09-15.
 * @author vsweatherfield
 */

#ifndef PDP11_EMULATOR_COMMANDS_H
#define PDP11_EMULATOR_COMMANDS_H

#include "types/CommandType.h"

extern Command commands[];

void do_nothing();

/**
 * @brief halts program execution and displays necessary data
 */
void do_halt();

/**
 * @brief moves source value to the destination, similar to pdp11 mov command
 */
void do_mov();

/**
 * @brief moves source byte value to the destination, similar to pdp11 movb
 * command
 */
void do_movb();

/**
 * @brief adds source value to the destination, similar to pdp11 add command
 */
void do_add();

/**
 * @brief increments the destination value, similar to pdp11 inc command
 */
void do_inc();

/**
 * @brief sets the processor state word, similar to pdp11 tst command
 */
void do_tst();

/**
 * @brief similar to the tst function above, but applied to bytes
 */
void do_tstb();

/**
 * @brief sets flags relative to the words ss - dd, similar to pdp11 cmp command
 */
void do_cmp();

/**
 * @brief similar to the cmp function above, but applied to bytes
 */
void do_cmpb();

/**
 * @brief decrements pc by 2 until the value in the register is zero, similar to
 * pdp11 sob command
 */
void do_sob();

/**
 * @brief resets the value in the register, similar to pdp11 clr command
 */
void do_clr();

/**
 * @brief unconditional jump to the given address, similar to pdp11 jmp command
 */
void do_jmp();

/**
 * @brief unconditional jump forward by 2 * xx, similar to pdp11 br command
 */
void do_br();

/**
 * @brief br command in case flag Z is set, similar to pdp11 beq command
 */
void do_beq();

/**
 * @brief br command in case flag N is not set, similar to pdp11 bpl command
 */
void do_bpl();

/**
 * @brief similar to pdp11 jsr command
 */
void do_jsr();

/**
 * @brief similar to pdp11 rts command
 */
void do_rts();

/**
 * @brief similar to pdp11 rol command
 */
void do_rol();

/**
 * @brief similar to the rol command, but applicable to bytes
 */
void do_rolb();

#endif  // PDP11_EMULATOR_COMMANDS_H
