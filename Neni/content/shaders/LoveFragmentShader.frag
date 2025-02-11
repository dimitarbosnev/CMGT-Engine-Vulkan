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
	vec2 windowSize;
}ubo;

void main() {
	vec2 pos = gl_FragCoord.xy / vec2(ubo.windowSize.x,ubo.windowSize.y);
	vec4 color1 = vec4(0.44, 0.02, 0.14,1);
	vec4 color2 = vec4(0.92, 0.41, 0.55,1);
	vec4 out_color = mix(color2,color1,pos.y);
    outColor = out_color * vec4(max(dot(ubo.dirLight.xyz,normalize(fragNormal)),0)*ubo.dirLight.w + ubo.ambientLight.xyz*ubo.ambientLight.w,1);
}