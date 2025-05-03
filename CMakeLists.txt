cmake_minimum_required(VERSION 3.26)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/toolchain-arm-gcc.cmake")

project(mzp C ASM)

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/arch/mzp_link.ld")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
  "${CMAKE_SOURCE_DIR}/arch/src/mzp_ivt.S"
  "${CMAKE_SOURCE_DIR}/arch/src/mzp_start.S"
  "${CMAKE_SOURCE_DIR}/example/main.c"
)

target_compile_options(${PROJECT_NAME} PRIVATE
  -mcpu=cortex-m0plus -mthumb -Wall -Wextra -g -Og -nostartfiles -nostdlib
)
# -g -O0 -O3 -flto -ffunction-sections -fdata-sections

target_link_options(${PROJECT_NAME} PRIVATE
        "-Wl,--defsym,MZP_STACK_SIZE=512"
  -T${LINKER_SCRIPT}
  -mcpu=cortex-m0plus -mthumb -g -nostartfiles -nostdlib
)
# -Wl,--gc-sections,-Map=${PROJECT_NAME}.map

target_include_directories(${PROJECT_NAME} PRIVATE 
  "${CMAKE_SOURCE_DIR}/arch/include"
)