//
// Created by vsweatherfield on 2021-09-15.
//

#ifndef PDP11_EMULATOR_ARGUMENTTYPE_H
#define PDP11_EMULATOR_ARGUMENTTYPE_H

#include "../constants/MemConstants.h"

typedef struct Arg {
    word val;
    word adr;
} Arg;

#endif // PDP11_EMULATOR_ARGUMENTTYPE_H