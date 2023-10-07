//
// Created by vsweatherfield on 2021-09-15.
//

#include "Commands.h"

#include <assert.h>
#include <stdlib.h>

#include "constants/MemConstants.h"
#include "constants/EmulatorConstants.h"
#include "constants/ArgConstants.h"

#include "tracer/Tracer.h"
#include "memory/Memory.h"
#include "process_state/ProcessState.h"
#include "argument_parsers/ArgumentParsers.h"

Command commands[] = {
    {0170000, 0010000, "mov", HAS_DD | HAS_SS, do_mov},
    {0170000, 0110000, "movb", HAS_DD | HAS_SS | HAS_B, do_movb},
    {0170000, 0060000, "add", HAS_DD | HAS_SS, do_add},
    {0177777, 0000000, "halt", NO_PARAMS, do_halt},
    {0177700, 0005200, "inc", HAS_DD, do_inc},
    {0177700, 0005700, "tst", HAS_DD, do_tst},
    {0177700, 0105700, "tstb", HAS_DD | HAS_B, do_tstb},
    {0170000, 0020000, "cmp", HAS_DD | HAS_SS, do_cmp},
    {0170000, 0120000, "cmpb", HAS_DD | HAS_SS | HAS_B, do_cmpb},
    {0177000, 0077000, "sob", HAS_NN | HAS_R, do_sob},
    {0177700, 0005000, "clr", HAS_DD, do_clr},
    {0177400, 0000100, "jmp", HAS_DD, do_jmp},
    {0177400, 0000400, "br", HAS_XX, do_br},
    {0177400, 0001400, "beq", HAS_XX, do_beq},
    {0177400, 0100000, "bpl", HAS_XX, do_bpl},
    {0177000, 0004000, "jsr", HAS_R | HAS_DD, do_jsr},
    {0177770, 0000200, "rts", HAS_R, do_rts},
    {0177700, 0006100, "rol", HAS_DD, do_rol},
    {0177700, 0106100, "rolb", HAS_DD | HAS_B, do_rolb},
    {0000000, 0000000, "unknown", NO_PARAMS, do_nothing}};

void do_nothing() { trace(TRACE, "\n"); }

void do_halt() {
    trace(INFO, "\n");
    fulltrace();
    trace(TRACE, "\n");
    trace(INFO, "---------------- halted ---------------\n");

    for (int i = 0; i < 8; i += 2) {
        trace(INFO, "%s=%06o ", print_register(i), reg[i]);
    }
    trace(INFO, "\n");

    for (int i = 1; i < 8; i += 2) {
        trace(INFO, "%s=%06o ", print_register(i), reg[i]);
    }

    char* nzvc_flags = display_nzvc_flags();
    trace(INFO, "\npsw=%06o\t\t      %s    \n", proc_state_word, nzvc_flags);
    free(nzvc_flags);
}

void do_mov() {
    proc_state_word = set_processor_state(ss.val, 0) | (proc_state_word & 1);
    write_word(dd.adr, ss.val, is_register_address(dd.adr));

    trace(TRACE, " \t\t[%06o]=%06o", ss.adr,
          read_word(ss.adr, is_register_address(ss.adr)));

    if (dd.adr == odata) {
        trace(QUIET, "%c", read_word(dd.adr, is_register_address(dd.adr)));
    }
    trace(TRACE, "\n");

    fulltrace();
}

void do_movb() {
    write_byte(dd.adr, ss.val, is_register_address(dd.adr));
    proc_state_word =
        set_processor_state(ss.val >> 7 ? ss.val | 0xFF00 : ss.val, 0) |
        (proc_state_word & 1);

    is_register_address(ss.adr) ? trace(TRACE, " \t\tR%o=", ss.adr)
                                : trace(TRACE, " \t[%06o]=", ss.adr);
    trace(TRACE, "%03o", read_byte(ss.adr, is_register_address(ss.adr)));

    if (dd.adr == odata) {
        trace(TRACE, " [%06o] ", dd.adr);
        trace(QUIET, "%c", read_byte(dd.adr, is_register_address(dd.adr)));
    }
    trace(TRACE, "\n");

    fulltrace();
}

void do_add() {
    write_word(dd.adr, ss.val + dd.val, is_register_address(dd.adr));
    proc_state_word = set_processor_state(ss.val, dd.val);

    is_register_address(ss.adr)
        ? trace(TRACE, "\t\t\tR%o=%06o ", ss.adr,
                read_word(ss.adr, is_register_address(ss.adr)))
        : trace(TRACE, "\t\t[%06o]=%06o ", ss.adr,
                read_word(ss.adr, is_register_address(ss.adr)));

    is_register_address(dd.adr)
        ? trace(TRACE, "R%o=%06o\n", dd.adr,
                read_word(dd.adr, is_register_address(dd.adr)))
        : trace(TRACE, "[%06o]=%06o\n", dd.adr,
                read_word(dd.adr, is_register_address(dd.adr)));

    fulltrace();
}

void do_inc() {
    write_word(dd.adr, dd.val + 1, is_register_address(dd.adr));
    proc_state_word = set_processor_state(dd.val, 1) | (proc_state_word & 1);

    is_register_address(dd.adr)
        ? trace(TRACE, "\t  R%o=%06o\n", dd.adr,
                read_word(dd.adr, is_register_address(dd.adr)))
        : trace(TRACE, "\t[%06o]=%06o\n", dd.adr,
                read_word(dd.adr, is_register_address(dd.adr)));

    fulltrace();
}

void do_tst() {
    proc_state_word = set_processor_state(dd.val, 0);

    is_register_address(dd.adr) ? trace(TRACE, "\t\tR%o=%06o\n", dd.adr, dd.val)
                                : trace(TRACE, "[%06o]=%06o\n", dd.adr, dd.val);

    fulltrace();
}

void do_tstb() {
    proc_state_word = dd.val >> 6 != 0 ? set_processor_state(dd.val | 0xFF00, 0)
                                       : set_processor_state(dd.val, 0);

    is_register_address(dd.adr)
        ? trace(TRACE, "\t\tR%o=%03o\n", dd.adr, dd.val)
        : trace(TRACE, "\t\t[%06o]=%03o\n", dd.adr, dd.val);

    fulltrace();
}

void do_cmp() {
    proc_state_word = set_processor_state(ss.val - dd.val, 0);

    fulltrace();
}

void do_cmpb() {
    proc_state_word = (ss.val - dd.val) >> 6 != 0
                          ? set_processor_state((ss.val - dd.val) | 0xFF00, 0)
                          : set_processor_state(ss.val - dd.val, 0);

    fulltrace();
}

void do_sob() {
    trace(TRACE, "%06o\n", pc - 2 * nn.val);

    --reg[r.adr];
    pc = (reg[r.adr] == 0 ? pc : pc - 2 * nn.val);

    fulltrace();
}

void do_clr() {
    reg[dd.adr] = 0;
    proc_state_word = set_processor_state(reg[dd.adr], 0);
    trace(TRACE, "\n");

    fulltrace();
}

void do_jmp() {
    assert(dd.adr % 2 == 0);
    pc = dd.adr;

    fulltrace();
}

void do_br() {
    pc += 2 * xx;

    fulltrace();
}

void do_beq() { flag_z() ? do_br() : fulltrace(); }

void do_bpl() { !flag_n() ? do_br() : fulltrace(); }

void do_jsr() {
    sp -= 2;
    write_word(sp, reg[r.adr], is_register_address(sp));

    reg[r.adr] = pc;
    pc = dd.adr;
    trace(TRACE, "\n");

    fulltrace();
}

void do_rts() {
    pc = reg[r.adr];

    reg[r.adr] = read_word(sp, is_register_address(sp));
    sp += 2;
    trace(TRACE, "\n");

    fulltrace();
}

void do_rol() {
    proc_state_word = set_processor_state(dd.val, dd.val);
    dd.val = (dd.val << 1) & 0xFFFE;

    write_word(dd.adr, dd.val, is_register_address(dd.adr));
    if (is_register_address(dd.adr)) {
        trace(TRACE, "\t\t\tR%o=%06o\n", dd.adr, dd.val);
    }

    fulltrace();
}

void do_rolb() {
    proc_state_word = set_processor_state(dd.val, dd.val + (dd.val >> 7));
    dd.val = ((dd.val << 1) & 0xFF) + (dd.val >> 7);

    write_byte(dd.adr, dd.val, is_register_address(dd.adr));
    is_register_address(dd.adr)
        ? trace(TRACE, "\t\t\tR%o=%06o\n", dd.adr, dd.val)
        : trace(TRACE, "\t\t\t[%06o]=%03o\n", dd.adr, dd.val);

    fulltrace();
}