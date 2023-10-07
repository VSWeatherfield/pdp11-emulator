//
// Created by vsweatherfield on 2021-09-16.
//

#include "ProcessState.h"

#include <stdlib.h>

#include "tracer/Tracer.h"
#include "memory/Memory.h"

word proc_state_word;

word set_processor_state(word word_0, word word_1) {
    word res = 0;

    if ((word_0 + word_1) >> 15 & 1) {  // negative flag
        res += 8;
    }

    if (((word_0 + word_1) & 0177777) == 0) {  // zero flag
        res += 4;
    }

    if (word_0 >> 15 == word_1 >> 15) {  // oVerflow flag
        if ((((word_0 + word_1) >> 15) & 1) != word_0 >> 15) {
            res += 2;
        }
    }

    if ((word_0 + word_1) >> 16) {  // carry flag
        res += 1;
    }

    return res;
}

char* display_nzvc_flags() {
    char* res = calloc(5, sizeof(char));
    char c = (global_tracer.level <= DEBUG) ? '-' : ' ';

    res[0] = flag_n() ? 'n' : c;
    res[1] = flag_z() ? 'z' : c;
    res[2] = flag_v() ? 'v' : c;
    res[3] = flag_c() ? 'c' : c;
    res[4] = '\0';

    return res;
}

void fulltrace() {
    char* nzvc_flags = display_nzvc_flags();
    char* reg_short_names[8] = {"0", "1", "2", "3", "4", "5", "S", "P"};

    trace(DEBUG, "%s ", nzvc_flags);

    for (int i = 0; i < 8; ++i) {
        trace(DEBUG, "%s:%06o ", reg_short_names[i], reg[i]);
    }
    trace(DEBUG, "\n");

    free(nzvc_flags);
}

int flag_n() { return (proc_state_word & 8) >> 3; }

int flag_z() { return (proc_state_word & 4) >> 2; }

int flag_v() { return (proc_state_word & 2) >> 1; }

int flag_c() { return (proc_state_word & 1); }