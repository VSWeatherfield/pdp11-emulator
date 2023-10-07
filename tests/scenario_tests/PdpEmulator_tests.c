#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants/EmulatorConstants.h"

#include "tracer/Tracer.h"
#include "memory/Memory.h"
#include "process_state/ProcessState.h"
#include "pdp_emulator/PdpEmulator.h"

#define TEST_DIR "../../../tests/assets/"
#define TEST_FILE(name) TEST_DIR name "/" name ".pdp.o"

static int TEST_NUM;

#define TEST_PACK(PACK) \
    printf(PACK);       \
    TEST_NUM = 1;

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

Tracer global_tracer;

int exec_mode = IMMEDIATE_MODE;

typedef struct {
    char* filename;
    word answers[9];
} test_data;

test_data tests[] = {
    {TEST_FILE("01_sum"),
     {000002, 000005, 000000, 000000, 000000, 000000, 000000, 001014, 000000}},
    {TEST_FILE("01_sum_mode1"),
     {000002, 000005, 000100, 000000, 000000, 000006, 000000, 001026, 000000}},
    {TEST_FILE("01_sum_mode1_big"),
     {012345, 012712, 000100, 000000, 000000, 60442, 000000, 001026, 000010}},
    {TEST_FILE("01_sum_neg"),
     {000003, 000001, 000000, 000000, 000000, 000000, 000000, 001014, 000001}},
    {TEST_FILE("02_sob"),
     {000133, 000000, 000110, 000066, 000000, 000000, 000000, 001022, 000000}},
    {TEST_FILE("02_sob_byte"),
     {000133, 000000, 000104, 000066, 000000, 000000, 000000, 001022, 000000}},
    {TEST_FILE("02_sob_mode3"),
     {000133, 000000, 000110, 000066, 000000, 000000, 000000, 001022, 000000}},
    {TEST_FILE("03_arr0"),
     {000133, 000000, 000112, 000000, 000000, 000000, 000000, 001020, 000004}},
    {TEST_FILE("03_arr0_byte"),
     {000133, 000000, 000105, 000000, 000000, 000000, 000000, 001020, 000004}},
    {TEST_FILE("07_putchar"),
     {000052, 000000, 000000, 000000, 000000, 000000, 000000, 001020, 000000}},
    {TEST_FILE("08_hello"),
     {000000, 000216, 000000, 000000, 000000, 000000, 000000, 001026, 000004}},
    {TEST_FILE("09_mode67"),
     {000000, 000000, 000000, 000000, 000000, 000000, 000000, 001016, 000000}},
    {TEST_FILE("09_mode6_minus"),
     {000204, 000000, 000000, 000000, 000000, 000000, 000000, 001026, 000000}},
    {TEST_FILE("09_mode6_plus"),
     {000200, 000000, 000000, 000000, 000000, 000000, 000000, 001022, 000000}},
    {TEST_FILE("10_jsr_rts"),
     {000000, 000216, 000000, 000000, 000000, 000000, 001000, 001016, 000004}},
    {TEST_FILE("10_jsr_sum"),
     {000133, 000000, 000112, 000000, 000000, 000000, 001000, 001020, 000004}},
    {TEST_FILE("10_jsr_sum_r5"),
     {000133, 000000, 000112, 000000, 005234, 000021, 001000, 001026, 000004}}};

void print_correct_registers(word answers[]) {
    char* nzvc_flags = display_nzvc_flags();
    char* reg_short_names[] = {"0", "1", "2", "3", "4", "5", "S", "P"};

    printf("%s ", nzvc_flags);

    for (int i = 0; i < 8; ++i) {
        printf("%s:%06o ", reg_short_names[i], answers[i]);
    }
    printf("\n");

    free(nzvc_flags);
}

void null_reg_mem_psw() {
    for (int i = 0; i < MEMSIZE; ++i) {
        mem[i] = 0;
    }

    for (int i = 0; i < REGSIZE; ++i) {
        reg[i] = 0;
    }

    proc_state_word = 0;
}

int check_registers_psw(word answers[]) {
    int everything_right = 1;
    for (int i = 0; i < 8; ++i) {
        if (reg[i] != answers[i] || proc_state_word != answers[8]) {
            everything_right = 0;
            break;
        }
    }
    return everything_right;
}

void test(const char* arg_0, const char* filename, word answers[]) {
    printf("[%d] ", TEST_NUM);
    load_file(arg_0, filename);
    word starting_address = DEFAULT_STARTING_ADDRESS;
    run(starting_address);

    if (!check_registers_psw(answers)) {
        printf("%s[FAILED]%s %-50s\n", RED, RESET, filename);
        printf("Expected Register values are:\n");
        print_correct_registers(answers);
        exit(EXIT_FAILURE);
    }

    printf("%s[PASSED]%s %-50s\n", GREEN, RESET, filename);
    ++TEST_NUM;

    null_reg_mem_psw();
}

int main(int argc, char* argv[]) {
    set_trace_level(&global_tracer, TEST);

    static const char* const test_types[] = {
        "Summation tests", "Loop(sob) tests", "Iteration(arr) tests",
        "Printing tests",  "Mode6 tests",     "Subroutine tests"};

    static const int test_indices[][2] = {{0, 4},  {4, 7},   {7, 9},
                                          {9, 11}, {11, 14}, {14, 17}};

    for (int i = 0; i < 6; ++i) {
        printf("\n%s\n", test_types[i]);
        TEST_NUM = 1;

        for (int j = test_indices[i][0]; j < test_indices[i][1]; ++j) {
            test(argv[0], tests[j].filename, tests[j].answers);
        }
    }

    exit(EXIT_SUCCESS);
}