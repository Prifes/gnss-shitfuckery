add_library(board-config STATIC)

add_subdirectory(cmake/stm32cubemx EXCLUDE_FROM_ALL)
target_link_libraries(board-config PRIVATE stm32cubemx)

target_include_directories(board-config PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32cubemx/Inc
    ${CMAKE_SOURCE_DIR}/src/bsp
)

target_sources(board-config PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/bsp/bsp.cpp
)