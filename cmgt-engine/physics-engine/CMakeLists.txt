file(GLOB_RECURSE CPP_Files ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp)


#find_package(nlohmann_json CONFIG REQUIRED)


add_library(physics-engine STATIC ${CPP_Files})
target_include_directories(physics-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)
target_link_libraries(physics-engine  
    PUBLIC 
    core
    minimal
)
#target_compile_definitions(core PUBLIC _USE_MATH_DEFINES)