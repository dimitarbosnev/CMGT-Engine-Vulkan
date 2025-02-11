#version 450

layout(location = 0) in vec4 fragColor;

layout(location = 1) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform Push {
    mat4 mvpMatrix;
    mat4 modelMatrix;
} push;

layout(set = 0, binding = 0) uniform UBOS{
	mat4 cameraMatrix;
	mat4 projMatrix;
	vec4 ambientLight;
	vec4 dirLight;
}ubo;

void main() {
    outColor = vec4(.3,.6,.6,1) * vec4(max(dot(ubo.dirLight.xyz,fragNormal),0)*ubo.dirLight.w + ubo.ambientLight.xyz*ubo.ambientLight.w,1);
}