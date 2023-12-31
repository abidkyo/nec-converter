/*------------------------------------------------------------------------------
 * @file nec.c
 *
 * @brief NEC IR Hex Converter
 *
 *----------------------------------------------------------------------------*/


#include <stdio.h>
#include <math.h>
#include "nec.h"


static void fillPreamble(NecData* data, uint32_t freq);
static void fillMessage(NecData* data, uint32_t freq, uint32_t ir_code);
static void fillRepeat(NecData* data, uint32_t freq);
static const char* dataToHexCode(NecData* data);
static const char* irCodeToBinary(uint32_t ir_code);


const char* nec_converter(uint32_t freq, uint32_t ir_code) {
    NecData data = {0};

    // fill data
    fillPreamble(&data, freq);
    fillMessage(&data, freq, ir_code);
    fillRepeat(&data, freq);

    // convert data to hex code and return it
    return dataToHexCode(&data);
}


static void fillPreamble(NecData* data, uint32_t freq) {
    data->preamble.zeros = 0;
    data->preamble.freq = round(1000000 / 0.241246 / freq);
    data->preamble.messagePair = sizeof(data->message) / 2 / 2;
    data->preamble.repeatPair = sizeof(data->repeat) / 2 / 2;
}


static void fillMessage(NecData* data, uint32_t freq, uint32_t ir_code) {
    uint8_t pulseCount = 0;

    // get binary representation of IR code
    const char* irCodeBin = irCodeToBinary(ir_code);

    // pulse length = 562.5 μs * frequency
    float pulseLength = 562.5 * freq / 1000000;

    data->message.pulse = round(16 * pulseLength);
    data->message.space = round(8 * pulseLength);

    int index = 0;
    for (int i = 0; i < 32; i++) {
        // pulse burst
        data->message.code[index++] = round(pulseLength);

        // pulse space according to binary
        if (irCodeBin[i] == 1) {
            data->message.code[index++] = round(3 * pulseLength);
            pulseCount += 4;
        }
        else {
            data->message.code[index++] = round(pulseLength);
            pulseCount += 2;
        }
    }

    // add pulse count from leading pulse, leading space and end pulse
    pulseCount += 16 + 8 + 1;

    data->message.end = round(pulseLength);
    data->message.pause = round((192 - pulseCount) * pulseLength);
}


static void fillRepeat(NecData* data, uint32_t freq) {
    // pulse length = 562.5 μs * frequency
    float pulseLength = 562.5 * freq / 1000000;

    data->repeat.pulse = round(16 * pulseLength);
    data->repeat.space = round(4 * pulseLength);
    data->repeat.end = round(pulseLength);
    data->repeat.pause = round(171 * pulseLength);
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
