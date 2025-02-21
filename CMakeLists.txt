cmake_minimum_required(VERSION 3.27)
message("${CMAKE_TOOLCHAIN_FILE}")
project(CMGT-Engine)
message("****************************** Configuring Project '${CMAKE_PROJECT_NAME}' ******************************************")
set(CMAKE_CXX_STANDARD 20)
set(VCPKG_TARGET_ARCHITECTURE x64)
# Enable includes for some simd instructions in clang.

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/binary)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/run)
set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(VULKAN_SHADER_COMPILER $ENV{VULKAN_SDK}/Bin/glslc.exe)


add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(cmgt-engine)


