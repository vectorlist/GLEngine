
#version 450 core

in vec3 inColor;

uniform sampler2D diffuse_map;
uniform sampler2D normal_map;


//from vert
in vec3 outPos;
in vec2 outCoords;
in mat3 TBNview;
in vec3 outNormal;
in float outFrame;
in float texindex;
out vec4 fragColor;


vec3 testShading(vec3 light, vec3 normal)
{
    float distance = length(light - outPos);
    vec3 lightDir = normalize(light - outPos);
    
    float d = max(dot(normalize(normal),lightDir),0.0);
    //invert lightDir
    
    vec3 ref = normalize(reflect(-lightDir, normal));
    vec3 viewDir = normalize(-outPos);
    
    //view dot reflect
    float vr = dot(viewDir, ref);
    float shine = 100;
    float p = pow(max(vr,0.0), shine);
    //vec3 spec = p * vec3(1);
    
    return vec3(1,1,1) * d;
}

void main()
{
    float f = abs(sin(outFrame * 0.01)) * 10;
    vec3 lightPos = vec3(3,2+f,3);
    vec3 outColor = inColor;
    vec3 normal = texture(normal_map, outCoords).rgb;
    vec3 base = texture(diffuse_map, outCoords).rgb;
    //tangent normal
    vec3 tbn = normalize(TBNview *(normal * 2.0 - vec3(1.0)));
    
    //base *= testShading(lightPos, tbn);
    vec3 result;
    if(texindex > 0){
	result = normal;
    }
    else{
	result = base * testShading(lightPos, outNormal);
    }
    
    fragColor = vec4(result,1);
}