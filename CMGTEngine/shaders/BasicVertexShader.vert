#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec3 fragNormal;
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
    gl_Position = push.mvpMatrix * vec4(position,1.0);
    fragNormal = mat3(push.modelMatrix) * normal;
}