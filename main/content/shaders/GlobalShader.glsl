struct Light{
    int type;
    vec3 color;
    vec3 direction;
    vec3 position;
    vec3 cut_off_angle;
    float intencity;
    float range;
};
layout(std140, set = 0, binding = 0) uniform GlobalUniforms{
	mat4 viewMatrix;
	mat4 projMatrix;
    uint lightCount;
}globals;

layout(set = 0, binding = 1) buffer LightBuffer {
    Light lights[]; // unsized array
}array;
