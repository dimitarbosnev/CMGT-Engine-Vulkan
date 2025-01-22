file(GLOB_RECURSE CPP_Files ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp)


find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

add_library(render-engine STATIC ${CPP_Files})
target_include_directories(render-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)
target_link_libraries(render-engine
    PUBLIC 
    Vulkan::Vulkan
    glfw
    core
    utils
)

#target_compile_definitions(core PUBLIC _USE_MATH_DEFINES)