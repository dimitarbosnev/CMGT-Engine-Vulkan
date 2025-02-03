file(GLOB_RECURSE CPP_Files ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp)

add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CPP_Files})
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)
target_link_libraries(main 
    PUBLIC 
    core 
    vulkan-api
    utils
    physics-engine
)

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/shaders
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/models
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/models)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/textures
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/textures)           

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/build/vcpkg_installed/x64-windows-static-md/bin/VkLayer_khronos_validation.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/build/vcpkg_installed/x64-windows-static-md/bin/VkLayer_khronos_validation.json
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})