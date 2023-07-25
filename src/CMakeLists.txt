cmake_minimum_required(VERSION 3.15)
project(freertos_msp430fr4133 C)
include(FetchContent)

# Global options
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR msp430)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(FETCHCONTENT_QUIET FALSE)

# Build options
set(TARGET_DEVICE MSP430FR4133)
set(TARGET_INCLUDE_DIR /usr/msp430-gcc-support-files/include)
set(CMAKE_C_COMPILER /usr/bin/msp430-elf-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/msp430-elf-g++)
add_compile_definitions(__${TARGET_DEVICE}__)
add_compile_options(-Wall -Werror -O3 -ffreestanding -save-temps)
include_directories(/usr/msp430-gcc-support-files/include)

# FreeRTOS Kernel
FetchContent_Declare(
    freertos_kernel
    GIT_REPOSITORY  https://github.com/FreeRTOS/FreeRTOS-Kernel.git
    GIT_TAG         V10.6.0
    GIT_PROGRESS    TRUE
    GIT_SHALLOW     TRUE
    GIT_SUBMODULES  ""
)

# FreeRTOS Target Port
FetchContent_Declare(
    freertos_kernel_port
    GIT_REPOSITORY
    git@github.com:stgloorious/freertos-port-gcc-msp430fr4133.git
    GIT_TAG             master
    GIT_PROGRESS        TRUE
    GIT_SHALLOW         TRUE
    GIT_SUBMODULES      ""
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
)

# FreeRTOS configuration
add_library(freertos_config INTERFACE)
target_include_directories(
    freertos_config
    SYSTEM INTERFACE
    include
)

target_compile_definitions(
    freertos_config
    INTERFACE
    projCOVERAGE_TEST=0
)
set(FREERTOS_HEAP "4" CACHE STRING "" FORCE)

# Port for target device
set(FREERTOS_PORT A_CUSTOM_PORT CACHE STRING "")
add_library(freertos_kernel_port INTERFACE)
target_sources(
    freertos_kernel_port 
    PRIVATE
    _deps/freertos_kernel_port-src/GCC/${TARGET_DEVICE}/port.c
    _deps/freertos_kernel_port-src/GCC/${TARGET_DEVICE}/portmacro.h
    _deps/freertos_kernel_port-src/GCC/${TARGET_DEVICE}/data_model.h
    _deps/freertos_kernel_port-src/GCC/${TARGET_DEVICE}/portext.asm
)
target_include_directories(
    freertos_kernel_port
    INTERFACE
    build/_deps/freertos_kernel_port-src/GCC/${TARGET_DEVICE}
)

FetchContent_MakeAvailable(freertos_kernel)
FetchContent_MakeAvailable(freertos_kernel_port)
