struct Light{
    uint type;
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

layout(std430, set = 0, binding = 1) buffer LightBuffer {
    Light lights[];
}array;

vec3 directionalLight(Light light ,vec3 fragNormal){
    //check for color changes light.color is not used here 
    return light.color * (max(dot(light.direction,fragNormal),0) * light.intencity);
}
vec3 ambientLight(Light light){
    return light.color * light.intencity;
}
vec4 processLights(vec4 color, vec3 fragNormal){
    vec3 lightSum = vec3(0);
    for(int i = 0; i < globals.lightCount; i++){
        switch(array.lights[i].type){
            case 0:
                lightSum += ambientLight(array.lights[i]);
            break;
            case 1:
                lightSum += directionalLight(array.lights[i], fragNormal);
            break;
            case 2:
            break;
            case 3:
            break;
        }
    }
    return color * vec4(array.lights[0].color,1);
}