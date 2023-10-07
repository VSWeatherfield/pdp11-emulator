//
// Created by vsweatherfield on 2021-09-19.
//

#include "StartupConfig.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "constants/EmulatorConstants.h"

#include "tracer/Tracer.h"
#include "pdp_emulator/PdpEmulator.h"

void usage(const char* filename) {
    fprintf(stderr,
            "\nUsage: %s [options] initial-core-file\n"
            "\nOptions:\n"
            "\t-s N\tstarting address, octal (default 1000)\n"
            "\t-n\tstep mode, command is executed after pressing the 'n' key\n"
            "\t-q\tquiet, don't show anything except target's output\n"
            "\t-t\tshow trace to stdout\n"
            "\t-T\tshow verbose trace to stdout\n\n",
            filename);

    exit(EXIT_FAILURE);
}

void parse_arguments(int argc, char* argv[], word* starting_address) {
    int opt;

    while ((opt = getopt(argc, argv, "s:nqtT")) != -1) {
        switch (opt) {
            case 's':
                starting_address = (word*)strtol(optarg, NULL, 8);
                break;
            case 'n':
                exec_mode = STEP_MODE;
                break;
            case 'q':
                set_trace_level(&global_tracer, QUIET);
                break;
            case 't':
                set_trace_level(&global_tracer, TRACE);
                break;
            case 'T':
                set_trace_level(&global_tracer, DEBUG);
                break;
            default: /* '?' */
                usage(argv[0]);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "\nError: missing initial core file\n");
        usage(argv[0]);
    }

    if (optind != argc - 1) {
        fprintf(stderr, "\nError: only one initial core file is needed\n");
        usage(argv[0]);
    }
}