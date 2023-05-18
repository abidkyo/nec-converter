# set cmake version
cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "nec_converter")

# set project details
project(
  ${PROJECT_NAME}
  VERSION 0.1
  DESCRIPTION "NEC IR Hex Converter"
  LANGUAGES C)

# enable compile command
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

