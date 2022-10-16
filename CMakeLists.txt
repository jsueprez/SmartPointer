cmake_minimum_required(VERSION 3.5)

set(PROJECT_CODE_NAME "SmartPointer")

project(${PROJECT_CODE_NAME} LANGUAGES CXX)

######################################################################################
# Compiler specific configurations
######################################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

######################################################################################
# Definition of the source/headers files
######################################################################################
set(CORE_SOURCE
    src/module/dummyLib.cpp
)

set(CORE_HEADERS
    src/module/dummyLib.h
)

file(GLOB TEST_SOURCE
    src/test/dummy_Unittest.cpp
    src/test/main.cpp
    src/test/dummy_PerformanceTest.cpp
)

set(ALL_SRC_CODE ${CORE_SOURCE} ${CORE_HEADERS})

include_directories(src)
include_directories(src/module)

######################################################################################
# Source code static library
######################################################################################
add_library(${PROJECT_CODE_NAME}_library STATIC ${ALL_SRC_CODE})

######################################################################################
# Adding Executable
######################################################################################
add_executable(${PROJECT_CODE_NAME}_executable src/main.cpp)
target_link_libraries(${PROJECT_CODE_NAME}_executable ${PROJECT_CODE_NAME}_library)

##TODO: Update to ExternalProject_Add
######################################################################################
# Google Test Framework
######################################################################################
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(src/ext/google/googletest)
include_directories (
    src/ext/google/googletest/googletest/src
    ${CMAKE_SOURCE_DIR}/src/ext/google/googletest/googletest/src
)

######################################################################################
# Google Benchmark Framework
######################################################################################
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark testing" FORCE)
set(BENCHMARK_ENABLE_EXCEPTIONS OFF CACHE BOOL "Disable benchmark exceptions" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Don't install benchmark" FORCE)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES OFF CACHE BOOL "Don't download dependencies" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable Google Test in benchmark" FORCE)

add_subdirectory(src/ext/google/benchmark)
include_directories(src/ext/google/benchmark/src ${CMAKE_SOURCE_DIR}/src/ext/google/benchmark)

add_executable(${PROJECT_CODE_NAME}_tests ${TEST_SOURCE})
target_link_libraries(${PROJECT_CODE_NAME}_tests
                      ${PROJECT_CODE_NAME}_library gtest benchmark::benchmark)

######################################################################################
# Adding CMAKE Test
######################################################################################
add_test(test_name ${PROJECT_CODE_NAME}_tests)

