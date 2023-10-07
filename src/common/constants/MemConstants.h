//
// Created by vsweatherfield on 2021-09-15.
//

#ifndef PDP11_EMULATOR_MEMCONSTANTS_H
#define PDP11_EMULATOR_MEMCONSTANTS_H

#include <stdint.h>

typedef int8_t byte;    // 8 bit
typedef uint16_t word;  // 16 bit
typedef word address;   // 16 bit

#define MEMSIZE (64 * 1024)
#define REGSIZE 8

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define pc reg[7]
#define sp reg[6]
#define odata 0177566
#define ostat 0177564

#endif // PDP11_EMULATOR_MEMCONSTANTS_H