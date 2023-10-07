/**
 * @file ProcessState.h
 *
 * This file contains declarations for PDP-11 NZVC (Negative, Zero,
 * Overflow, Carry) flags and the operations associated with them
 * within the PDP-11 emulator. The processor state word, typically
 * represented as a single machine word, contains these flags.
 *
 * @date Created on 2021-09-16.
 * @author vsweatherfield
 */

#ifndef PDP11_EMULATOR_PROCESSSTATE_H
#define PDP11_EMULATOR_PROCESSSTATE_H

#include "constants/MemConstants.h"

extern word proc_state_word;

/**
 * @brief update processor state word, set nzvc flags (one machine word)
 */
word set_processor_state(word word_0, word word_1);

char* display_nzvc_flags();

void fulltrace();

/**
 * @return return value is greater than zero if flag n is on
 */
int flag_n();

/**
 * @return return value is greater than zero if flag z is on
 */
int flag_z();

/**
 * @return return value is greater than zero if flag v is on
 */
int flag_v();

/**
 * @return return value is greater than zero if flag c is on
 */
int flag_c();

#endif  // PDP11_EMULATOR_PROCESSSTATE_H
