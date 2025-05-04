# BME Suborbitals | STM32 Project Template
Universal project template for any STM32 based project.

## Setup
1. Clone the repository
2. Initialize submodules using `git submodule update --init --recursive`
3. Generate board specific code using CubeMX under `board/`
   1. Configure pins and the clock
   2. In the *Project Manager* tab be sure to:
      - Check *Do not generate main()*
      - For the *Toolchain / IDE* select *CMake*
      - Select *Copy only the necessary library files*
      - Check *Generate peripheral initialization as a pair of '.c/.h' files per peripheral*
	3. Generate code
4. Update the `CMakeLists`
   1. In the root level `CMakeLists.txt` include the generated files using `add_subdirectory(board/your-board)`
   2. Replace `board/your-board/CMakeLists.txt` with
		```cmake
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
		```
	3. In `board/your-board/cmake/gcc-arm-none-eabi.cmake` replace `set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -T \"${CMAKE_SOURCE_DIR}/stm32h725vgtx_flash.ld\"")` with `set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -T \"${CMAKE_CURRENT_LIST_DIR}/../stm32h725vgtx_flash.ld\"")`
	4. Update the toolchain file path in `CMakePresets.json` to point to your boards toolchain `"toolchainFile": "${sourceDir}/board/your-board/cmake/gcc-arm-none-eabi.cmake",`
5. Add your board specific funcion implementations to `board/your-board/bsp/bsp.cpp`
6. If needed, you can add multiple different board configurations to the same project

## Project Outline
Once setup is complete, your project should look something like 
```
project/
├─ board/               (contains all board / MCU specific files)
│  ├─ nucleo/           (configuration for testing with a Nucleo)
│  │  └─ bsp/           (implementation of hadware specific functions)
│  └─ flight-computer/  (configuration for the final hardware)
│     └─ bsp/           (implementation of hardware specific funcitons)
├─ lib/                 (any external dependencies)
└─ src/                 (project source files)
   ├─ bsp/              (interface of required hardware specific functions)
   └─ main.cpp          (entry point for the application)
```
