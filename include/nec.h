/*------------------------------------------------------------------------------
 * @file nec.h
 *
 * @brief Header for NEC IR Hex Converter
 *
 *----------------------------------------------------------------------------*/

#ifndef NEC_H
#define NEC_H


#include <stdint.h>


#define NEC_FREQUENCY 38000  // Hz

// data and hex code size (see NecData struct); divide by 2 bytes (uint16_t)
#define NEC_DATA_SIZE ((sizeof(NecPreamble) + sizeof(NecMessage) + sizeof(NecRepeat)) / 2)
#define NEC_HEXCODE_SIZE (NEC_DATA_SIZE * 5)  // multiply by 5 (4 digits plus space)


typedef struct {
    uint16_t zeros;  // always zero
    uint16_t freq;
    uint16_t messagePair;  // byte pairs count
    uint16_t repeatPair;  // byte pairs count
} __attribute__((packed)) NecPreamble;

typedef struct {
    uint16_t pulse;
    uint16_t space;
    uint16_t code[32 * 2];  // 32-bit pairs
    uint16_t end;
    uint16_t pause;
} __attribute__((packed)) NecMessage;

typedef struct {
    uint16_t pulse;
    uint16_t space;
    uint16_t end;
    uint16_t pause;
} __attribute__((packed)) NecRepeat;

typedef union {
    struct {
        NecPreamble preamble;
        NecMessage message;
        NecRepeat repeat;
    } __attribute__((packed));
    uint16_t all[NEC_DATA_SIZE];
} __attribute__((packed)) NecData;


const char* nec_converter(uint32_t ir_code);


#endif  // NEC_H

/*----------------------------------------------------------------------------*/
