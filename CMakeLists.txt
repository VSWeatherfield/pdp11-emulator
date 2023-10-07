cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD 11)

set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()

set (FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

message("generator is set to ${CMAKE_GENERATOR}")

set(LIBNAME "PDP11EmulatorLib")
set(TESTNAME "PDP11EmulatorTests")

project(${LIBNAME} VERSION 1.0.0)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(AddGitSubmodule)
include(Docs)

add_subdirectory(src)

project(${TESTNAME})

add_git_submodule(src/utils/unity)

enable_testing()
add_subdirectory(tests)

project(PDP11Emulator)

set(CMAKE_C_FLAGS_RELEASE "-O3")

include_directories(src)

add_executable(PDP11Emulator main.c)
target_link_libraries(PDP11Emulator Common Core)