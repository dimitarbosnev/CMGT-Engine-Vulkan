#file(GLOB_RECURSE CPP_Files ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp)


find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
set(VULKAN_SDK $ENV{VULKAN_SDK})

add_library(minimal INTERFACE)
target_include_directories(minimal INTERFACE
${VULKAN_SDK}/Include
 ${CMAKE_CURRENT_SOURCE_DIR}/header)
target_link_directories(minimal  INTERFACE ${VULKAN_SDK}/Lib)
target_link_libraries(minimal INTERFACE glm::glm vulkan-1)
#target_compile_definitions(core PUBLIC _USE_MATH_DEFINES)