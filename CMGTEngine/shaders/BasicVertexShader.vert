#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

layout(location = 0) out vec4 fragColor;
layout(push_constant) uniform Push {
    mat4 mvpMatrix;
    float offset;
} push;

void main() {
    gl_Position =push.mvpMatrix * vec4(position,1.0);
    fragColor = vec4(normal,1.0);
}