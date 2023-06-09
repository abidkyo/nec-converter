/*------------------------------------------------------------------------------
 * @file test_nec.c
 *
 * @brief Test NEC IR Hex Converter
 *
 *----------------------------------------------------------------------------*/


#include "unity.h"
#include "nec.h"


void setUp(void) {
}

void tearDown(void) {
}


void testNec(void) {
    /* IrScruntinizer result; 38000 Hz, 0x00FF00FF
     * 0000 006D 0022 0002 0157 00AB
     * 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015
     * 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040
     * 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015
     * 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040
     * 0015 05E7 0157 0056 0015 0E46 */
    const char* expected =
        "0000 006D 0022 0002 0156 00AB "
        "0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 "
        "0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 "
        "0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 "
        "0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 "
        "0015 05EE 0156 0056 0015 0E47";

    uint32_t irCode = 0x00FF00FF;
    const char* hexCode = nec_converter(irCode);

    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected, hexCode, NEC_HEXCODE_SIZE);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testNec);
    return UNITY_END();
}


/*--------------------------------------------------------------------------------*/
