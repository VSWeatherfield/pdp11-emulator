//
// Created by vsweatherfield on 2021-09-15.
//

#ifndef PDP11_EMULATOR_MODE_TYPE_H
#define PDP11_EMULATOR_MODE_TYPE_H

#include "ArgumentType.h"

typedef struct {
    int mode_num;
    void (*do_mode)(Arg* res, word rgstr);
} Mode;

#endif // PDP11_EMULATOR_MODE_TYPE_H