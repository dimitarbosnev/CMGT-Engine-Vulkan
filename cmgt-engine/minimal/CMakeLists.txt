#file(GLOB_RECURSE CPP_Files ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp)


find_package(glm REQUIRED)

find_package(Vulkan REQUIRED)

add_library(minimal INTERFACE)
target_include_directories(minimal INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/header)
target_link_libraries(minimal INTERFACE glm::glm  Vulkan::Vulkan)
#target_compile_definitions(core PUBLIC _USE_MATH_DEFINES)