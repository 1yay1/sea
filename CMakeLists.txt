cmake_minimum_required(VERSION 2.6)
project(sea)
SET(CMAKE_CXX_FLAGS -pthread)
set(PROJECT_SOURCE_DIR .)

set(COVERAGE OFF CACHE BOOL "Coverage")

# Project Structure
set(LIBRARY_OUTPUT_PATH lib)                                    # generated library files
set(EXECUTABLE_OUTPUT_PATH bin)                                 # generated binary files
set(CMAKE_INCLUDE_PATH include/)

set(CMAKE_INCLUDE_CURRENT_DIR OFF)
set(WARNING_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -Wdeprecated")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Werror -Wdocumentation")
endif()
set(BUILD_FLAGS "-std=c++11 -O3 -fno-builtin -fno-rtti -ffast-math ${WARNING_FLAGS}")
set(TEST_FLAGS "-std=c++11 -g -O0 -fno-builtin -fno-rtti -ffast-math ${WARNING_FLAGS}")

# --------------------------------------------------- #
#                   Dependencies
# --------------------------------------------------- #
include(ExternalProject)
find_program(MAKE NAMES cmake make)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# --------------------------------------------------- #
#                   gtest library
# --------------------------------------------------- #
ExternalProject_Add(GTEST_PROJECT
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG dea0216d0c6bc5e63cf5f6c8651cd268668032ec
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/third-party/gtest
        CMAKE_ARGS -DINSTALL_GTEST=OFF -DCMAKE_CXX_FLAGS=-std=c++11 -fpermissive -stdlib=libc++
        INSTALL_COMMAND ""
        BUILD_COMMAND "${MAKE}" --build .)

ExternalProject_Get_Property(GTEST_PROJECT source_dir)
ExternalProject_Get_Property(GTEST_PROJECT binary_dir)
set(GOOGLETEST_ROOT ${source_dir})
set(GOOGLETEST_BIN ${binary_dir})
MESSAGE(STATUS "GTest source_dir: ${GOOGLETEST_ROOT}")
MESSAGE(STATUS "GTest build_dir: ${GOOGLETEST_BIN}")

include_directories(SYSTEM ${GOOGLETEST_ROOT}/googletest/)
include_directories(SYSTEM ${GOOGLETEST_ROOT}/googletest/include)
add_library(gtest STATIC IMPORTED)
add_dependencies(gtest GTEST_PROJECT)
set_property(TARGET gtest PROPERTY IMPORTED_LOCATION "${GOOGLETEST_BIN}/googlemock/gtest/libgtest.a")

# --------------------------------------------------- #
#                   build library
# --------------------------------------------------- #
include_directories(${CMAKE_INCLUDE_PATH})
file(GLOB LIB_SOURCES "src/*.cpp" "src/*/*.cpp")

add_library(sealib SHARED ${LIB_SOURCES})

# --------------------------------------------------- #
#                   build tests
# --------------------------------------------------- #
file(GLOB TESTS "test/*.cpp")                                   # all test files
add_executable(tests ${LIB_SOURCES} ${TESTS})
add_dependencies(tests gtest)
set(TEST_LINK_FLAGS "")

if (COVERAGE)
        MESSAGE(STATUS "Link Coverage")
        set(TEST_FLAGS "${TEST_FLAGS} --coverage")
        set(TEST_LINK_FLAGS "--coverage")
elseif (PROFILING AND ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
        MESSAGE(STATUS "Profiling: ENABLED")
        set(TEST_FLAGS "${TEST_FLAGS} -pg -no-pie")
        set(TEST_LINK_FLAGS "-pg -no-pie")
endif ()

# --------------------------------------------------- #
#                   build main
# --------------------------------------------------- #
file(GLOB MAIN "src-view/*.cpp")                                   # all test files
add_executable(main ${LIB_SOURCES} ${MAIN})

find_package(Threads)
set_target_properties(main PROPERTIES LINK_FLAGS "${CMAKE_THREAD_LIBS_INIT}")
set_target_properties(tests PROPERTIES LINK_FLAGS "${TEST_LINK_FLAGS} ${CMAKE_THREAD_LIBS_INIT}")
target_link_libraries(tests gtest)

set_target_properties(sealib main PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})
set_target_properties(tests PROPERTIES COMPILE_FLAGS ${TEST_FLAGS})