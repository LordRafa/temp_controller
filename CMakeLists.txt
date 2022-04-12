# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/lordrafa/bin/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(temp_controller C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_subdirectory (lib/picoLCD)

file(GLOB_RECURSE FILES src/*.c)
add_executable( temp_controller ${FILES} )

include_directories(${PROJECT_SOURCE_DIR}/include/)

pico_set_program_name(temp_controller "temp_controller")
pico_set_program_version(temp_controller "0.1")

pico_enable_stdio_uart(temp_controller 1)
pico_enable_stdio_usb(temp_controller 1)

# Add the standard library to the build
target_link_libraries(temp_controller pico_stdlib hardware_adc hardware_pwm hardware_clocks picoLCD)

pico_add_extra_outputs(temp_controller)

