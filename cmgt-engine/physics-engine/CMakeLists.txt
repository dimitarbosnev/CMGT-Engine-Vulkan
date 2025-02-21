file(GLOB_RECURSE CPP_Files ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp)

add_library(physics-engine STATIC ${CPP_Files})
target_include_directories(physics-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)
target_link_libraries(physics-engine  
    PUBLIC 
    core
    minimal
)