<!-- ----------------------------------------------------------------------- -->

# NEC IR Hex Converter

Convert IR code into Hex code.

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
