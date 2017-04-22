#pragma once

#include <GL/glew.h>
#include <vec3f.h>
#include <vector>
//uniform buffer
#define LIGHT_MAX_NUM		3
#define LIGHT_TYPE_SIZE		28
//#define LIGHT_POINTER(x) ##&x[0]

typedef struct
{
	vec3f position;   //float 4 x 3  12
	vec3f color;		//float 4 x4 12
	vec3f attenuation;	
	
}UBOLight;

class Light
{
public:
	Light();
	~Light();

	void initLightUniform(std::vector<GLuint> &shaders);
	void setLight();
	void debug_bindUniform(); // update

	GLuint ubo;
	static std::vector<GLuint> light_shaers;
	static UBOLight ubo_lights[LIGHT_MAX_NUM];
	uint32_t enabled_lights_num = 3;

};

