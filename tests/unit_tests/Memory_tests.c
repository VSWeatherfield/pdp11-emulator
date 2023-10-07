#include "unity.h"
#include "memory/Memory.h"

void setUp() {
}

void tearDown() {
}

void test_read_byte_write_byte() {
    address a = 2;
    byte b0 = 0x0a;

    write_byte(a, b0, 0);
    byte b_res = read_byte(2, 0);

    TEST_ASSERT_EQUAL_HEX8(b0, b_res);
}

void test_read_word_write_byte() {
    address a = 4;
    byte b1 = 0x0b;
    byte b0 = 0x0a;
    word w = 0x0b0a;

    write_byte(a, b0, 0);
    write_byte(a + 1, b1, 0);
    word w_res = read_word(a, 0);

    TEST_ASSERT_EQUAL_HEX16(w, w_res);
}

void test_read_byte_write_word() {
    address a = 2;
    byte b0 = 0x0b;
    byte b1 = 0xba;
    word w = 0xba0b;

    write_word(a, w, 0);
    byte b_res0 = read_byte(a, 0);
    byte b_res1 = read_byte(a + 1, 0);

    TEST_ASSERT_EQUAL_HEX8(b0, b_res0);
    TEST_ASSERT_EQUAL_HEX8(b1, b_res1);
}

void test_read_word_write_word() {
    address a = 16;
    word w = 0x090a;

    write_word(a, w, 0);
    word wres = read_word(a, 0);

    TEST_ASSERT_EQUAL_HEX16(w, wres);
}

int main(int argc, char* argv[]) {
    UNITY_BEGIN();

    RUN_TEST(test_read_byte_write_byte);
    RUN_TEST(test_read_word_write_byte);
    RUN_TEST(test_read_byte_write_word);
    RUN_TEST(test_read_word_write_word);

    return UNITY_END();
}