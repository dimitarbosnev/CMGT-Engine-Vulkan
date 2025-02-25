
# The name of a new project
set(PROJ_NAME test_cmgt)
# DO NOT TOUCH CRUTIAL FOR LOCATING STUFF
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/${PROJ_NAME})
set(ASSET_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/assets)


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

add_custom_target(${PROJ_NAME}_Copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${ASSET_FOLDER}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test/assets
    COMMENT "Copying textures directory"
)

add_dependencies(${PROJ_NAME}
${PROJ_NAME}_Copy_assets
)   
