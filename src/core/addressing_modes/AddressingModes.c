//
// Created by vsweatherfield on 2021-09-15.
//

#include "AddressingModes.h"

#include <assert.h>

#include "memory/Memory.h"
#include "tracer/Tracer.h"
#include "argument_parsers/ArgumentParsers.h"

Mode modes[] = {
    {0, do_mode_0},       {1, do_mode_1}, {2, do_mode_2}, {3, do_mode_3},
    {4, do_mode_4},       {5, do_mode_5}, {6, do_mode_6}, {7, do_mode_7},
    {-1, do_unknown_mode}  // catch-all entry for unknown modes
};

void do_mode_0(Arg* res, word rgstr) {
    assert(rgstr < 8);

    res->adr = rgstr;
    res->val = reg[rgstr];

    trace(TRACE, "%s", print_register(rgstr));
}

void do_mode_1(Arg* res, word rgstr) {
    assert(rgstr < 8);

    res->adr = reg[rgstr];
    res->val = read_value(res->adr, b.val);

    trace(TRACE, "(%s)", print_register(rgstr));
}

void do_mode_2(Arg* res, word rgstr) {
    res->adr = reg[rgstr];
    res->val = read_value(res->adr, b.val);

    if (rgstr == 7) {
        pc += 2;
        trace(TRACE, "#%06o", res->val);
    } else if (rgstr == 6) {
        sp += 2;
        trace(TRACE, "(%s)+", print_register(rgstr));
    } else {
        reg[rgstr] += (b.val ? 1 : 2);
        trace(TRACE, "(%s)+", print_register(rgstr));
    }
}

void do_mode_3(Arg* res, word rgstr) {
    res->adr = read_word(reg[rgstr], is_register_address(reg[rgstr]));
    res->val = read_value(res->adr, b.val);

    reg[rgstr] += 2;

    if (rgstr == 7) {
        trace(TRACE, "@#%06o", res->adr);
    } else {
        trace(TRACE, "@(%s)+", print_register(rgstr));
    }
}

void do_mode_4(Arg* res, word rgstr) {
    if (rgstr >= 6) {
        //    assert(reg[rgstr] >= 2);
        reg[rgstr] -= 2;
    } else {
        reg[rgstr] -= (b.val ? 1 : 2);
    }

    res->adr = reg[rgstr];
    res->val = read_value(res->adr, b.val);

    trace(TRACE, "-(%s)", print_register(rgstr));
}

void do_mode_5(Arg* res, word rgstr) {
    assert(reg[rgstr] >= 2);
    reg[rgstr] -= 2;
    res->adr = read_word(reg[rgstr], is_register_address(reg[rgstr]));
    res->val = read_value(res->adr, b.val);

    trace(TRACE, "@-(%s)", print_register(rgstr));
}

void do_mode_6(Arg* res, word rgstr) {
    word index = read_word(pc, is_register_address(pc));
    pc += 2;

    res->adr = reg[rgstr] + index;
    res->val = read_value(res->adr, b.val);

    rgstr < 7 ? trace(TRACE, "%06o(%s)", index, print_register(rgstr))
              : trace(TRACE, "%06o ", res->adr);
}

void do_mode_7(Arg* res, word rgstr) {
    word index = read_word(pc, is_register_address(pc));
    pc += 2;

    res->adr =
        read_word(reg[rgstr] + index, is_register_address(reg[rgstr] + index));
    res->val = read_value(res->adr, b.val);

    trace(TRACE, "@%06o(%s)", index, print_register(rgstr));
}

void do_unknown_mode(Arg* res, word rgstr) {
    UNUSED(res);
    UNUSED(rgstr);

    trace(INFO, "MODE IS NOT IMPLEMENTED YET OR IS NOT RECOGNIZED\n");
}
