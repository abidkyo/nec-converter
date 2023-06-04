# fetch content feature
include(FetchContent)

# fetch and add unity (testing library)
FetchContent_Declare(
    unity
    GIT_REPOSITORY "https://github.com/ThrowTheSwitch/Unity.git"
    GIT_TAG "v2.5.2"
)
FetchContent_MakeAvailable(unity)

# add executable with main file
add_executable(${TEST_NAME} test_nec.c)

# link with library
target_link_libraries(${TEST_NAME} PRIVATE ${LIB_NAME} unity)

# add test
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

