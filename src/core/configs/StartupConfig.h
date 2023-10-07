//
// Created by vsweatherfield on 2021-09-15.
//

#ifndef PDP11_EMULATOR_STARTUPCONFIG_H
#define PDP11_EMULATOR_STARTUPCONFIG_H

#include "constants/MemConstants.h"

void usage(const char* filename);

void parse_arguments(int argc, char* argv[], word* starting_address);

#endif // PDP11_EMULATOR_STARTUPCONFIG_H
