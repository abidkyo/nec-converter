# add library
add_library(${LIB_NAME})

target_compile_options(${LIB_NAME} PRIVATE -Wall)

# set source files
target_sources(${LIB_NAME} PRIVATE nec.c)

# set header directory
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

