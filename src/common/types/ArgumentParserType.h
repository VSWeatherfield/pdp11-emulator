//
// Created by vsweatherfield on 2021-09-15.
//

#ifndef PDP11_EMULATOR_ARGUMENTPARSERTYPE_H
#define PDP11_EMULATOR_ARGUMENTPARSERTYPE_H

#include "../constants/MemConstants.h"
#include "CommandType.h"

typedef struct {
    int arg_opcode;
    void (*handle_arg)(Command cmd, word w);
} Arg_batch;

#endif // PDP11_EMULATOR_ARGUMENTPARSERTYPE_H