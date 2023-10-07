//
// Created by vsweatherfield on 2021-09-15.
//

#ifndef PDP11_EMULATOR_COMMANDTYPE_H
#define PDP11_EMULATOR_COMMANDTYPE_H

#include "../constants/MemConstants.h"

typedef struct {
    word mask;
    word opcode;
    char* name;
    char params;
    void (*do_func)(void);
} Command;

#endif // PDP11_EMULATOR_COMMANDTYPE_H