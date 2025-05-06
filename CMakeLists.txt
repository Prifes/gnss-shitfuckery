cmake_minimum_required(VERSION 3.28.1)

# Change to your project name
project(stm32-template ASM C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(UTILS_INCLUDE_DEBUG ON)

# Include board configuration
add_subdirectory(board/athenavi)
add_subdirectory(lib/utils)
add_subdirectory(lib/drivers)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    src/
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    stm32cubemx
    board-config
    utils
    drivers
)

target_link_libraries(drivers PRIVATE stm32cubemx)