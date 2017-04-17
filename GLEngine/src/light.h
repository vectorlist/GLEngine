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
	float intensity;	// 4
	//28 size
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

//// Create a uniform buffer object
//// First. We get the relevant block indices
//GLuint uniformBlockIndexRed = glGetUniformBlockIndex(shaderRed.Program, "Matrices");
//GLuint uniformBlockIndexGreen = glGetUniformBlockIndex(shaderGreen.Program, "Matrices");
//GLuint uniformBlockIndexBlue = glGetUniformBlockIndex(shaderBlue.Program, "Matrices");
//GLuint uniformBlockIndexYellow = glGetUniformBlockIndex(shaderYellow.Program, "Matrices");
//// Then we link each shader's uniform block to this uniform binding point
//glUniformBlockBinding(shaderRed.Program, uniformBlockIndexRed, 0);
//glUniformBlockBinding(shaderGreen.Program, uniformBlockIndexGreen, 0);
//glUniformBlockBinding(shaderBlue.Program, uniformBlockIndexBlue, 0);
//glUniformBlockBinding(shaderYellow.Program, uniformBlockIndexYellow, 0);
//// Now actually create the buffer
//GLuint uboMatrices;
//glGenBuffers(1, &uboMatrices);
//glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
//glBindBuffer(GL_UNIFORM_BUFFER, 0);
//// Define the range of the buffer that links to a uniform binding point
//glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
//// Store the projection matrix (we only have to do this once) (note: we're not using zoom anymore by changing the FoV. We only create the projection matrix once now)
//glm::mat4 projection = glm::perspective(45.0f, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
//glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
//glBindBuffer(GL_UNIFORM_BUFFER, 0);
//// Game loop
//while (!glfwWindowShouldClose(window))
//{
//	// Set frame time
//	GLfloat currentFrame = glfwGetTime();
//	deltaTime = currentFrame - lastFrame;
//	lastFrame = currentFrame;
//	// Check and call events
//	glfwPollEvents();
//	Do_Movement();
//	// Clear buffers
//	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	// Set the view and projection matrix in the uniform block - we only have to do this once per loop iteration.
//	glm::mat4 view = camera.GetViewMatrix();
//	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4),
//		sizeof(glm::mat4), glm::value_ptr(view));
//	glBindBuffer(GL_UNIFORM_BUFFER, 0);
//
//
//	#version 330 core
//		layout(location = 0) in vec3 position;
//
//	layout(std140) uniform Matrices
//	{
//		mat4 projection;
//		mat4 view;
//	};
//


//glGetActiveUniformBlockiv(programHandle, blockIndex,
//	GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
//
//GLubyte * blockBuffer = (GLubyte *)malloc(blockSize);
//
//Query for the offset of each variable within the block.To do so, we first find the index of each variable within the block.
//// Query for the offsets of each block variable
//const GLchar *names[] = { "InnerColor", "OuterColor",
//"RadiusInner", "RadiusOuter" };
//
//GLuint indices[4];
//glGetUniformIndices(programHandle, 4, names, indices);
//
//GLint offset[4];
//glGetActiveUniformsiv(programHandle, 4, indices,
//	GL_UNIFORM_OFFSET, offset);
//
//Place the data into the buffer at the appropriate offsets.
//GLfloat outerColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
//GLfloat innerColor[] = { 1.0f, 1.0f, 0.75f, 1.0f };
//GLfloat innerRadius = 0.25f, outerRadius = 0.45f;
//
//memcpy(blockBuffer + offset[0], innerColor,
//	4 * sizeof(GLfloat));
//memcpy(blockBuffer + offset[1], outerColor,
//	4 * sizeof(GLfloat));
//memcpy(blockBuffer + offset[2], &innerRadius,
//	sizeof(GLfloat));
//memcpy(blockBuffer + offset[3], &outerRadius,
//	sizeof(GLfloat));
//
//Create the OpenGL buffer object and copy the data into it.
//GLuint uboHandle;
//glGenBuffers(1, &uboHandle);
//glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
//glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer,
//	GL_DYNAMIC_DRAW);
//
//Bind the buffer object to the uniform block.
//glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, uboHandle);