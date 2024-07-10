#version 450

layout(location = 0) in vec4 fragColor;

layout(location = 1) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform Push {
    mat4 mvpMatrix;
    mat4 modelMatrix;
} push;

//Light direction and light intensity
const vec4 dirLight = vec4(normalize(vec3(1,-1,1)),1);
//Light color and light intensity
const vec4 ambientLight = vec4(1,1,1,.2); 
void main() {
    outColor = vec4(.3,.6,.6,1) * vec4(max(dot(dirLight.xyz,fragNormal),0)*dirLight.w + ambientLight.xyz*ambientLight.w,1);
}