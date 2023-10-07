//
// Created by vsweatherfield on 2021-09-19.
//

#include "Tracer.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

Tracer global_tracer;

void set_trace_level(Tracer* tracer, Trace_level level) {
    tracer->level = level;
}

void trace(Trace_level level, const char* format, ...) {
    if (level < global_tracer.level) {
        return;
    }

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

char* print_register(word reg_num) {
    char* registers[8] = {"r0", "r1", "r2", "r3", "r4", "r5", "sp", "pc"};
    assert(reg_num < 8);

    return registers[reg_num];
}