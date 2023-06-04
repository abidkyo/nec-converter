# set cmake version
cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "nec_converter")
set(LIB_NAME "nec_lib")
set(TEST_NAME "nec_test")

# set project details
project(
  ${PROJECT_NAME}
  VERSION 0.1
  DESCRIPTION "NEC IR Hex Converter"
  LANGUAGES C)

# enable compile command
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add library in src
add_subdirectory(src)

# test only if this is main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # enable testing
  include(CTest)

  # add test directory
  add_subdirectory(tests)
endif()

