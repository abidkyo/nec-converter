<!-- ----------------------------------------------------------------------- -->

# NEC IR Hex Converter

Convert IR code into Hex code.

## NEC Infrared Transmission Protocol

### Reference

- https://techdocs.altium.com/display/FPGA/NEC+Infrared+Transmission+Protocol
- http://www.hifi-remote.com/infrared/IR-PWM.shtml

### Description

- pulse distance encoding of message bit
- standard frequency is 38 kHz, period is approx. 26.3 μs
- each pulse burst is 562.5 μs
- logic bits:
  - '0' --> 562.5 μs pulse burst followed by a 562.5 μs space; total = 1.125 ms
  - '1' --> 562.5 μs pulse burst followed by a 1687.5 μs space; total = 2.25 ms
- duration of single frame transmission = 108 ms (192 pulse burst and space)

### Preamble Code

- zero (0x00)
- IR frequency (see [below](#ir-frequency-in-hex))
- message code byte pairs (NEC: 34 byte pairs = 0x22)
- repeat code byte pairs (NEC: 2 byte pairs = 0x02)

#### IR Frequency in Hex

```c
hex_irFreq = 1000000 / 0.241246 / irFreq;
```

### Message Code

- leading pulse burst (16x = 9 ms)
- leading space (8x = 4.5 ms)
- 8-bit address
- logical inverse of 8-bit address
- 8-bit command
- logical inverse of 8-bit command
- end pulse burst (1x = 562.5 μs)
- end space (71x = 39.9375 ms)

address + command --> 96x = 54 ms

#### Notes

End space duration can vary if address or command has different formats, e.g:

- 8-bit address + 8-bit command (as shown [above](#message-code))
- 16-bit address + 8-bit command
- 16-bit address + 16-bit command

### Repeat Code

- leading pulse burst (16x = 9 ms)
- repeat space (4x = 2.25 ms)
- end pulse burst (1x = 562.5 μs)
- end space (171x = 96.1875 ms)

## Requirement

- CMake 3.22 or newer
- gcc toolchain
- make or Ninja

## Compile and Build Instructions

```sh
# configure project with make (default):
cmake -S . -B build/

# configure project with ninja:
cmake -GNinja -S . -B build/

# build project
cmake --build build/

# run test
cd build/ && ctest
```

<!-- ----------------------------------------------------------------------- -->
