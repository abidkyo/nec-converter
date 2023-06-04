/*------------------------------------------------------------------------------
 * @file nec.c
 *
 * @brief NEC IR Hex Converter
 *
 *----------------------------------------------------------------------------*/


#include <stdio.h>
#include "nec.h"


// pulse length = 562.5 μs * frequency
#define PULSE_LENGTH (562.5 * NEC_FREQUENCY / 1000000)


static void fillPreamble(NecData* data);
static void fillMessage(NecData* data, uint32_t ir_code);
static void fillRepeat(NecData* data);
static const char* dataToHexCode(NecData* data);
static const char* irCodeToBinary(uint32_t ir_code);


const char* nec_converter(uint32_t ir_code) {
    static NecData data = {0};

    // fill data
    fillPreamble(&data);
    fillMessage(&data, ir_code);
    fillRepeat(&data);

    // convert data to hex code and return it
    return dataToHexCode(&data);
}


static void fillPreamble(NecData* data) {
    data->preamble.zeros = 0;
    data->preamble.freq = 1000000 / 0.241246 / NEC_FREQUENCY;
    data->preamble.messagePair = sizeof(data->message) / 2 / 2;
    data->preamble.repeatPair = sizeof(data->repeat) / 2 / 2;
}


static void fillMessage(NecData* data, uint32_t ir_code) {
    // get binary representation of IR code
    const char* irCodeBin = irCodeToBinary(ir_code);

    data->message.pulse = 16 * PULSE_LENGTH;
    data->message.space = 8 * PULSE_LENGTH;

    int index = 0;
    for (int i = 0; i < 32; i++) {
        // pulse burst
        data->message.code[index++] = PULSE_LENGTH;

        // pulse space according to binary
        if (irCodeBin[i] == 1) {
            data->message.code[index++] = 3 * PULSE_LENGTH;
        }
        else {
            data->message.code[index++] = PULSE_LENGTH;
        }
    }

    data->message.end = PULSE_LENGTH;
    data->message.pause = 71 * PULSE_LENGTH;
}


static void fillRepeat(NecData* data) {
    data->repeat.pulse = 16 * PULSE_LENGTH;
    data->repeat.space = 4 * PULSE_LENGTH;
    data->repeat.end = PULSE_LENGTH;
    data->repeat.pause = 171 * PULSE_LENGTH;
}


static const char* dataToHexCode(NecData* data) {
    static char hexCode[NEC_HEXCODE_SIZE] = {0};

    // "0000 006D 0022 0002 0156 00AB ..."
    int index = 0;
    for (int i = 0; i < NEC_DATA_SIZE; i++) {
        index += snprintf(&hexCode[index], NEC_HEXCODE_SIZE - index, "%04X ", data->all[i]);
    }

    return hexCode;
}


static const char* irCodeToBinary(uint32_t ir_code) {
    static char binary[sizeof(ir_code) * 8] = {0};

    uint8_t* byte = (uint8_t*)&ir_code;
    size_t idx = 0;

    // loop every byte
    for (int i = sizeof(ir_code) - 1; i >= 0; i--) {
        // loop every bit
        for (int j = 7; j >= 0; j--) {
            if ((byte[i] >> j) & 1) {
                binary[idx] = 1;
            }
            else {
                binary[idx] = 0;
            }
            idx++;
        }
    }

    return binary;
}


/*--------------------------------------------------------------------------------*/
