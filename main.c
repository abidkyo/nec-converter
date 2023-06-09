/*------------------------------------------------------------------------------
 * @file main.c
 *
 * @brief Main for NEC IR Hex Converter
 *
 *----------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include "nec.h"


int main(int argc, char* argv[]) {
    // return error if not enough argument
    if (argc < 3) {
        return 1;
    }

    uint32_t freq = strtoul(argv[1], NULL, 10);
    uint32_t irCode = strtoul(argv[2], NULL, 16);

    const char* hexCode = nec_converter(freq, irCode);
    printf("freq: %u, code: %08X\n", freq, irCode);
    printf("%s\n", hexCode);

    return 0;
}


/*--------------------------------------------------------------------------------*/
