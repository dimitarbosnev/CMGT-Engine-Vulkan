
# The name of a new project
set(PROJ_NAME Neni)
# DO NOT TOUCH CRUTIAL FOR LOCATING STUFF
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJ_NAME})
set(PROJ_CONTENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/content)
set(OUT_CONTENT_FOLDER ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/content)

file(GLOB_RECURSE CPP_Files ${PROJ_CONTENT_FOLDER}/scripts/cpp/*.cpp)
add_executable(${PROJ_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CPP_Files})
target_include_directories(${PROJ_NAME} PUBLIC ${PROJ_CONTENT_FOLDER}/scripts/header)
target_link_libraries(${PROJ_NAME} 
    PUBLIC 
    core 
    vulkan-api
    utils
    physics-engine
)

# CUSTOM COMMANDS FOR PROJECTS

# Define a custom target for copying DLL and JSON files
add_custom_target(${PROJ_NAME}_CopyVkLayerFiles
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/build/vcpkg_installed/x64-windows-static-md/bin/VkLayer_khronos_validation.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VkLayer_khronos_validation.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/build/vcpkg_installed/x64-windows-static-md/bin/VkLayer_khronos_validation.json
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VkLayer_khronos_validation.json
    COMMENT "Copying VkLayer files if they have changed"
)

# Define a custom target for creating the shaders directory
# Define the output directory for compiled shaders
set(SHADER_OUTPUT_DIR ${OUT_CONTENT_FOLDER}/shaders)

# Gather all shader files
file(GLOB SHADERS
    ${PROJ_CONTENT_FOLDER}/shaders/*.vert
    ${PROJ_CONTENT_FOLDER}/shaders/*.frag
    ${PROJ_CONTENT_FOLDER}/shaders/*.comp
    ${PROJ_CONTENT_FOLDER}/shaders/*.geom
    ${PROJ_CONTENT_FOLDER}/shaders/*.tesc
    ${PROJ_CONTENT_FOLDER}/shaders/*.tese
    ${PROJ_CONTENT_FOLDER}/shaders/*.mesh
    ${PROJ_CONTENT_FOLDER}/shaders/*.task
    ${PROJ_CONTENT_FOLDER}/shaders/*.rgen
    ${PROJ_CONTENT_FOLDER}/shaders/*.rchit
    ${PROJ_CONTENT_FOLDER}/shaders/*.rmiss
)

# List to hold all SPIR-V output files
set(SPIRV_FILES)

# Loop through each shader and define custom commands
foreach(SHADER IN LISTS SHADERS)
    get_filename_component(FILENAME ${SHADER} NAME)
    set(SPV_FILE ${SHADER_OUTPUT_DIR}/${FILENAME}.spv)
    list(APPEND SPIRV_FILES ${SPV_FILE})

    add_custom_command(
        OUTPUT ${SPV_FILE}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADER_OUTPUT_DIR}
        COMMAND ${VULKAN_SHADER_COMPILER} ${SHADER} -o ${SPV_FILE}
        DEPENDS ${SHADER}
        COMMENT "Compiling ${FILENAME} to SPIR-V"
    )
endforeach()

# Define a custom target that depends on all SPIR-V files
add_custom_target(${PROJ_NAME}_CompileShaders
    DEPENDS ${SPIRV_FILES}
    COMMENT "Compiling all shaders"
)

# Define a custom target for copying models
add_custom_target(${PROJ_NAME}_CopyModels
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJ_CONTENT_FOLDER}/models
            ${OUT_CONTENT_FOLDER}/models
    COMMENT "Copying models directory"
)

# Define a custom target for copying textures
add_custom_target(${PROJ_NAME}_CopyTextures
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJ_CONTENT_FOLDER}/textures
            ${OUT_CONTENT_FOLDER}/textures
    COMMENT "Copying textures directory"
)

# Ensure the main project depends on these custom targets
add_dependencies(${PROJ_NAME}
${PROJ_NAME}_CopyVkLayerFiles
${PROJ_NAME}_CompileShaders
${PROJ_NAME}_CopyModels
${PROJ_NAME}_CopyTextures
)   
   
