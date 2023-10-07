//
// Created by vsweatherfield on 2021-09-19.
//

#ifndef PDP11_EMULATOR_TRACER_H
#define PDP11_EMULATOR_TRACER_H

#include "types/TracerType.h"
#include "constants/MemConstants.h"

extern Tracer global_tracer;

void set_trace_level(Tracer* tracer, Trace_level level);

void trace(Trace_level level, const char* format, ...);

char* print_register(word reg_num);

#endif // PDP11_EMULATOR_TRACER_H