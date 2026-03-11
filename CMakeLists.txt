# cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake

cmake_minimum_required(VERSION 3.16)

project(PRAC_STM32 C CXX ASM)

set(MCU "-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16")
set(DRIVER_LIB_NAME "cube_h503")
set(DEVICE_FAMILY_NAME "STM32H503xx")
set(C_FLAGS "${MCU} -Wall -Wextra -g3 -O0 --specs=nano.specs")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${C_FLAGS}")

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/Src/bsp/ldscript/STM32H503RBTX_FLASH.ld")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Map=${PROJECT_NAME}.map,--cref -Wl,--gc-sections ${MCU} -T${LINKER_SCRIPT}")

include_directories(
  Src
  Src/ap
  Src/bsp
  Src/common
  Src/common/hw/include
  Src/hw
  Src/lib/${DRIVER_LIB_NAME}/Drivers/CMSIS/Device/ST/STM32H5xx/Include
  Src/lib/${DRIVER_LIB_NAME}/Drivers/CMSIS/Include
  Src/lib/${DRIVER_LIB_NAME}/Drivers/BSP/STM32H5xx_Nucleo
  Src/lib/${DRIVER_LIB_NAME}/Drivers/STM32H5xx_HAL_Driver/Inc
)

file(GLOB SOURCES
  "Src/*.c" 
  "Src/ap/*.c" 
  "Src/bsp/*.c" 
  "Src/common/*.c" 
  "Src/hw/*.c" 
  "Src/hw/driver/*.c" 
  "Src/bsp/startup/startup_stm32h503rbtx.s"
  "Src/lib/${DRIVER_LIB_NAME}/Drivers/BSP/STM32H5xx_Nucleo/*.c"
  "Src/lib/${DRIVER_LIB_NAME}/Drivers/STM32H5xx_HAL_Driver/Src/*.c"
)
message(STATUS "Found source files: ${SOURCES}")

add_definitions(-D${DEVICE_FAMILY_NAME})

add_executable(${PROJECT_NAME}.elf ${SOURCES})

set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
  COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
  COMMENT "Building .hex and .bin files..."
)
