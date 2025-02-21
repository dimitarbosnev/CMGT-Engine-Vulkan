file(GLOB_RECURSE CPP_Files ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp)

add_library(utils STATIC ${CPP_Files})
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)
target_link_libraries(utils 
    PUBLIC 
    core
    vulkan-api
    minimal
    physics-engine
)
#target_compile_definitions(core PUBLIC _USE_MATH_DEFINES)