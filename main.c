#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "src/common/constants/EmulatorConstants.h"

#include "src/core/memory/Memory.h"
#include "src/core/pdp_emulator/PdpEmulator.h"
#include "src/core/tracer/Tracer.c"
#include "src/core/configs/StartupConfig.h"

int main(int argc, char* argv[]) {
    set_trace_level(&global_tracer, INFO);

    word starting_address = DEFAULT_STARTING_ADDRESS;
    parse_arguments(argc, argv, &starting_address);

    load_file(argv[0], argv[optind]);

    trace(INFO, "\n---------------- running --------------\n");
    run(starting_address);

    exit(EXIT_SUCCESS);
}