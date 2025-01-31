file(GLOB_RECURSE CPP_Files ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp)


find_package(Vulkan REQUIRED)

add_library(vulkan-api STATIC ${CPP_Files})
target_include_directories(vulkan-api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)
target_link_libraries(vulkan-api
    PUBLIC 
    Vulkan::Vulkan
    minimal
)

#target_compile_definitions(core PUBLIC _USE_MATH_DEFINES)