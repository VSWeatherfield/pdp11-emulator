//
// Created by vsweatherfield on 2021-09-15.
//

#include "ArgumentParsers.h"

#include "constants/ArgConstants.h"

#include "tracer/Tracer.h"
#include "memory/Memory.h"
#include "addressing_modes/AddressingModes.h"

// argument variables
Arg ss, dd, nn, n, r, b;
char xx;

Arg_batch args[] = {{HAS_B, handle_b_arg},      {HAS_R, handle_r_arg},
                    {HAS_SS, handle_ss_arg},    {HAS_DD, handle_dd_arg},
                    {HAS_NN, handle_nn_arg},    {HAS_XX, handle_xx_arg},
                    {NO_PARAMS, handle_nothing}};

Arg do_register_mode(word w) {
    Arg res;
    word rgstr = w & 7;
    Mode mode = modes[(w >> 3) & 7];

    mode.do_mode(&res, rgstr);
    return res;
}

void reset_arguments() {
    ss.val = 0;
    ss.adr = 0;

    dd.val = 0;
    dd.adr = 0;

    nn.val = 0;
    nn.adr = 0;

    n.val = 0;
    n.adr = 0;

    r.val = 0;
    r.adr = 0;

    b.val = 0;
    b.adr = 0;

    xx = 0;
}

void handle_nothing(Command cmd, word w) {
    UNUSED(cmd);
    UNUSED(w);
}

void handle_b_arg(Command cmd, word w) {
    UNUSED(cmd);

    Arg res;
    res.val = w >> 15;
    b = res;
}

Arg get_r(word w) {
    Arg res;
    res.adr = w & 7;
    return res;
}

void handle_r_arg(Command cmd, word w) {
    r = (cmd.opcode == 0000200) ? get_r(w) : get_r(w >> 6);
    trace(TRACE, "%s", print_register(r.adr));

    if (cmd.opcode != 0000200) {
        trace(TRACE, ",");
    }
}

void handle_ss_arg(Command cmd, word w) {
    UNUSED(cmd);

    ss = do_register_mode(w >> 6);
}

void handle_dd_arg(Command cmd, word w) {
    if ((cmd.params & HAS_SS) == HAS_SS) {
        trace(TRACE, ",");
    }

    dd = do_register_mode(w);
}

void handle_nn_arg(Command cmd, word w) {
    UNUSED(cmd);

    Arg res;
    res.val = w & 077;
    nn = res;
}

void handle_xx_arg(Command cmd, word w) {
    UNUSED(cmd);

    xx = w;
    trace(TRACE, "%06o\n", pc + 2 * xx);
}
