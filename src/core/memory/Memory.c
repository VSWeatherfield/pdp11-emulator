//
// Created by vsweatherfield on 2021-09-15.
//

#include "Memory.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

word mem[MEMSIZE];
word reg[REGSIZE];

byte read_byte(address addr, int from_reg) {
    if (from_reg) {
        return (byte)reg[addr];
    }

    if (addr % 2) {
        return (byte)((mem[addr - 1] >> 8) & 0xFF);
    } else {
        return (byte)(mem[addr] & 0xFF);
    }
}

void write_byte(address addr, byte val, int to_reg) {
    if (to_reg) {
        reg[addr] = val;
        return;
    }

    if (addr % 2) {
        mem[addr - 1] = ((word)val << 8) | (mem[addr - 1] & 0xFF);
    } else {
        mem[addr] = val | (mem[addr] & ~0xFF);
    }
}

word read_word(address addr, int from_reg) {
    if (from_reg) {
        return reg[addr];
    }

    assert(addr % 2 == 0);
    return mem[addr];
}

void write_word(address addr, word val, int to_reg) {
    if (to_reg) {
        reg[addr] = val;
        return;
    }

    assert(addr % 2 == 0);
    mem[addr] = val;
}

word read_value(address addr, word b_val) {
    return b_val ? read_byte(addr, is_register_address(addr))
                 : read_word(addr, is_register_address(addr));
}

void write_value(address addr, word val, word b_val) {
    b_val ? write_byte(addr, val, is_register_address(addr))
          : write_word(addr, val, is_register_address(addr));
}

int is_register_address(address addr) { return addr < 8; }

void load_file(const char* arg_0, const char* filename) {
    int res;
    byte x;
    word address, n;
    FILE* fin;
    fin = fopen(filename, "r");

    if (fin == NULL) {
        fprintf(stderr, "%s: can't open %s for reading\n", arg_0, filename);
        exit(EXIT_FAILURE);
    }

    while (2 == fscanf(fin, "%hx%hx", &address, &n)) {
        for (int i = 0; i < n; ++i) {
            res = fscanf(fin, "%hhx", &x);
            write_byte(address + i, x, is_register_address(address + i));
        }
    }

    fclose(fin);
}

void mem_dump(address start, word n) {
    for (int i = 0; i < n / 2; i++) {
        printf("%06o : %06o\n", start,
               read_word(start, is_register_address(start)));
        start += 2;
    }
}