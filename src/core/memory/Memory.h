//
// Created by vsweatherfield on 2021-09-15.
//

#ifndef PDP11_EMULATOR_MEMORY_H
#define PDP11_EMULATOR_MEMORY_H

#include "constants/MemConstants.h"

extern word mem[MEMSIZE];
extern word reg[REGSIZE];

/**
 * @brief read the byte value at the given address
 * @param addr - address to read from
 * @param from_reg - true if reading from register
 */
byte read_byte(address addr, int from_reg);

/**
 * @brief write the byte value to the given address
 * @param addr - address to write to
 * @param to_reg - true if writing to register
 */
void write_byte(address addr, byte val, int to_reg);

/**
 * @brief read the word value at the given address.
 *
 * In this project, the memory consists of 64kb of words, as opposed to the
 * original, which had just 64kb. Therefore, reading from an odd address is not
 * possible.
 * @param addr - address to read from
 * @param from_reg - true if reading from register
 */
word read_word(address addr, int from_reg);

/**
 * @brief write the word value at the given address.
 *
 * Writing to an odd address is not possible as with read_word function above.
 * @param addr - address to write to
 * @param to_reg - true if writing to register
 */
void write_word(address addr, word val, int to_reg);

/**
 * @brief reads word or byte depending on b argument
 */
word read_value(address addr, word b_val);

/**
 * @brief writes word or byte depending on b argument
 */
void write_value(address addr, word val, word b_val);

/**
 * @brief boolean whether memory address is register or not
 *
 * First 512 memory cells are reserved for the operating system,
 * therefore, accessing the first 8 cells is treated as accessing the registers
 * array.
 */
int is_register_address(address addr);

/**
 * @brief load prgram into memoy
 * @return pointer to string with register
 */
void load_file(const char* arg_0, const char* filename);

void mem_dump(address start, word n);

#endif  // PDP11_EMULATOR_MEMORY_H
