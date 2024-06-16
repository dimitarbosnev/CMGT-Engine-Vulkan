#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;

layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform Push {
    mat4 mvpMatrix;
    float offset;
} push;

void main() {
    gl_Position = push.mvpMatrix * vec4(position,1.0); //+ vec3(push.offset,0.0f,0.0f), 1.0);
    fragColor = color;
}