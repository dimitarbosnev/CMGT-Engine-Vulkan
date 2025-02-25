file(GLOB_RECURSE CPP_Files ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp)

find_package(Stb REQUIRED)

add_library(core STATIC ${CPP_Files})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header ${Stb_INCLUDE_DIR})
target_link_libraries(core  
    PUBLIC 
    vulkan-api
)
#target_compile_definitions(core PUBLIC _USE_MATH_DEFINES)