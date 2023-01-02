cmake_minimum_required(VERSION 3.14)

project(csig
    VERSION 0.2
    DESCRIPTION "signals and slots for C"
    LANGUAGES C)


# main settings
enable_testing()
include(FetchContent)


# add main source
add_subdirectory(src)

# add tests
add_subdirectory(tests)
#if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR CSIG_BUILD_TESTING) AND BUILD_TESTING)
    #add_subdirectory(tests)
#endif()
