//
// Created by vsweatherfield on 2021-09-16.
//

#include "PdpEmulator.h"

#include <stdio.h>

#include "constants/MemConstants.h"
#include "constants/ArgConstants.h"
#include "constants/EmulatorConstants.h"

#include "tracer/Tracer.h"
#include "memory/Memory.h"
#include "argument_parsers/ArgumentParsers.h"
#include "commands/Commands.h"

int exec_mode = IMMEDIATE_MODE;

void run(word starting_address) {
    pc = starting_address;
    write_word(ostat, 0000200, is_register_address(ostat));

    // loop through memory, reading instructions and parameters
    while (1) {
        if (exec_mode == STEP_MODE) {
            char symbol = '\0';
            while (symbol != 'n') {
                symbol = getchar();
            }
        }

        word current_word = read_word(pc, is_register_address(pc));
        trace(TRACE, "%06o: ", pc);
        pc += 2;

        for (int cmd_num = 0;; ++cmd_num) {
            Command cmd = commands[cmd_num];

            if ((current_word & cmd.mask) == cmd.opcode) {
                trace(TRACE, "%s\t", cmd.name);
                reset_arguments();

                // check which arguments are present and execute the
                // corresponding argument handlers
                for (int arg_num = 0;; ++arg_num) {
                    Arg_batch argument = args[arg_num];

                    if (argument.arg_opcode == NO_PARAMS) {
                        break;
                    }

                    if ((cmd.params & argument.arg_opcode) ==
                        argument.arg_opcode) {
                        argument.handle_arg(cmd, current_word);
                    }
                }

                cmd.do_func();

                if (cmd.mask == 0177777 && cmd.opcode == 0000000) {
                    return;
                }
                break;
            }
        }
    }
}