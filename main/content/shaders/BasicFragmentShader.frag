#version 450
#include "GlobalShader.glsl"

layout(location = 0) in vec4 fragColor;

layout(location = 1) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform Push {
    mat4 mvpMatrix;
    mat4 modelMatrix;
} push;

layout(std140, set = 1, binding = 0) uniform Uniforms{
	vec4 dirLight;
	vec4 ambientLight;
}ubo;

void main() {
    outColor = vec4(.3,.6,.6,1) * vec4(max(dot(ubo.dirLight.xyz,fragNormal),0)*ubo.dirLight.w + ubo.ambientLight.xyz*ubo.ambientLight.w,1);
}