#version 450
#include "GlobalShader.glsl"

layout(location = 0) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
    vec3 color;
} push;

void main() {
    outColor = processLights(vec4(push.color,1),fragNormal);
}