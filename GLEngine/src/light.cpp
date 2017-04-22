#include "light.h"

std::vector<GLuint> Light::light_shaers;
UBOLight Light::ubo_lights[LIGHT_MAX_NUM];

Light::Light()
{
}


Light::~Light()
{
}

//pass shader enable uniform lihgt only 
void Light::initLightUniform(std::vector<GLuint> &shaders)
{
	for (auto shader : shaders) {
		GLuint light_index = glGetUniformBlockIndex(shader, "light_block");
		//it will 0 index in glsl
		glUniformBlockBinding(shader, light_index, 0);
	}

	//fix later
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	//@param NULL is for dynamic at runtime
	//static atm
	glBufferData(GL_UNIFORM_BUFFER, LIGHT_MAX_NUM * sizeof(UBOLight), NULL,
		GL_STATIC_DRAW);
	//un bounding
	glBindBuffer(GL_UNIFORM_BUFFER, NULL);	

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, LIGHT_MAX_NUM * sizeof(UBOLight));

	glBindBuffer(GL_UNIFORM_BUFFER, ubo);

	glBufferSubData(GL_UNIFORM_BUFFER, 0, 
		sizeof(UBOLight), &ubo_lights[0]);

	//Bind the buffer object to the uniform block.
	//glBindBufferBase(GL_UNIFORM_BUFFER, ,, ubo);
	
}

void Light::setLight()
{

	/*ubo_lights[0].position = vec3f(10, 3, 0);
	ubo_lights[0].color = vec3f(1, 0, 0);
	ubo_lights[0].intensity = 0.8;

	ubo_lights[1].position = vec3f(0, 3, 10);
	ubo_lights[1].color = vec3f(0, 1, 0);
	ubo_lights[1].intensity = 0.8;

	ubo_lights[2].position = vec3f(10, 3, 10);
	ubo_lights[2].color = vec3f(0, 0, 1);
	ubo_lights[2].intensity = 0.8;*/
}

void Light::debug_bindUniform()
{
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	//@param must less than light num * light type size  // just arrray dont need to pointer address
	glBufferSubData(GL_UNIFORM_BUFFER, 0, LIGHT_MAX_NUM * LIGHT_TYPE_SIZE, ubo_lights);
	glBindBuffer(GL_UNIFORM_BUFFER, NULL);
}
