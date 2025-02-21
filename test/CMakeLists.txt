
# The name of a new project
set(PROJ_NAME test_cmgt)
# DO NOT TOUCH CRUTIAL FOR LOCATING STUFF
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY})



file(GLOB_RECURSE CPP_Files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${PROJ_NAME} ${CPP_Files})

find_package(doctest REQUIRED)

target_compile_options(${PROJ_NAME} PRIVATE -DDOCTEST_CONFIG_SUPER_FAST_ASSERTS)


target_include_directories(${PROJ_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)
target_link_libraries(${PROJ_NAME} 
    PUBLIC 
    core 
    utils
    physics-engine
    PRIVATE
    doctest::doctest
)
