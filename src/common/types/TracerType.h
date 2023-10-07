//
// Created by vsweatherfield on 2021-09-15.
//

#ifndef PDP11_EMULATOR_TRACER_TYPE_H
#define PDP11_EMULATOR_TRACER_TYPE_H

typedef enum { DEBUG, TRACE, INFO, QUIET, TEST } Trace_level;

typedef struct {
    Trace_level level;
} Tracer;

#endif // PDP11_EMULATOR_TRACER_TYPE_H