cmake_minimum_required(VERSION 3.28.1)

# Change to your project name
project(stm32-template ASM C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# Include board configuration
add_subdirectory(board/your-board)

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
)