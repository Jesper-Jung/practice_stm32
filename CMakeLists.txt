# cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake

cmake_minimum_required(VERSION 3.16)

project(PRAC_STM32 C CXX ASM)

set(MCU "-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16")
set(C_FLAGS "${MCU} -Wall -Wextra -g3 -O0 --specs=nano.specs")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${C_FLAGS}")

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/Src/bsp/ldscript/STM32H563ZITX_FLASH.ld")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Map=${PROJECT_NAME}.map,--cref -Wl,--gc-sections ${MCU} -T${LINKER_SCRIPT}")

include_directories(
  Inc
  Src
  Src/ap
  Src/bsp
  Src/common
  Src/hw
  Src/lib
)

file(GLOB SOURCES 
  "./Src/*.c" 
  "./Src/ap/*.c" 
  "./Src/bsp/*.c" 
  "./Src/common/*.c" 
  "./Src/hw/*.c" 
  "./Src/bsp/startup/*.s"
)

message(STATUS "Found source files: ${SOURCES}")

add_executable(${PROJECT_NAME}.elf ${SOURCES})

set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
  COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
  COMMENT "Building .hex and .bin files..."
)
