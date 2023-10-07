//
// Created by vsweatherfield on 2021-09-16.
//

#ifndef PDP11_EMULATOR_PDPEMULATOR_H
#define PDP11_EMULATOR_PDPEMULATOR_H

#include "constants/MemConstants.h"

extern int exec_mode;

void run(word starting_address);

#endif  // PDP11_EMULATOR_PDPEMULATOR_H
