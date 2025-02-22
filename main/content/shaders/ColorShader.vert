#version 450
#include "GlobalShader.glsl"

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

layout(location = 0) out vec3 fragNormal;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
    vec3 color;
} push;

void main() {
    mat4 modelMatrix = object.matrix[gl_InstanceIndex];
    gl_Position = (globals.projMatrix * globals.viewMatrix * modelMatrix) * vec4(position,1.0);
    fragNormal = transpose(inverse(mat3(modelMatrix))) * normal;
}