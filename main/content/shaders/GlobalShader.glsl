struct Light{
    uint type;
    float intencity;
    float range;
    vec3 color;
    vec3 direction;
    vec3 position;
    vec3 cut_off_angle;
};

layout(std140, set = 0, binding = 0) uniform GlobalUniforms{
	mat4 viewMatrix;
	mat4 projMatrix;
    uint lightCount;
}globals;

layout(std430, set = 0, binding = 1) readonly buffer MatrixBuffer {
    mat4 matrix[];
}object;

layout(std430, set = 0, binding = 2) readonly buffer LightBuffer {
    Light light_array[];
}lights;

vec3 directionalLight(Light light ,vec3 fragNormal){
    //check for color changes light.color is not used here 
    return light.color * (max(dot(light.direction,fragNormal),0) * light.intencity);
}
vec3 ambientLight(Light light){
    return light.color * light.intencity;
}
vec4 processLights(vec3 fragNormal){
    vec3 lightSum = vec3(0);
    for(int i = 0; i < globals.lightCount; i++){
        switch(lights.light_array[i].type){
            case 0:
                lightSum += ambientLight(lights.light_array[i]);
            break;
            case 1:
                lightSum += directionalLight(lights.light_array[i], fragNormal);
            break;
            case 2:
            break;
            case 3:
            break;
        }
    }
    return vec4(lightSum,1);
}