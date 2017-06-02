#include "shadowrenderer.h"
#include <shadertool.h>

const Matrix4x4 ShadowRenderer::bias{
	0.5, 0.0, 0.0, 0.5,
	0.0, 0.5, 0.0, 0.5,
	0.0, 0.0, 0.5, 0.5,
	0.0, 0.0, 0.0, 1.0
};

ShadowRenderer::ShadowRenderer(int windowWidth, int windowHeight, Camera &camera)
	: 
	frameBuffer(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, windowWidth, windowHeight),
	camera(camera),
	depthShader(LOAD_SHADER(DIR_SHADER"depthShadow.vert", DIR_SHADER"depthShadow.frag")),
	shadow_bbox(view, camera)
{

}

ShadowRenderer::~ShadowRenderer()
{
}

void ShadowRenderer::render(std::vector<entity_ptr>& entities, const vec3f& sun, const vec3f &at)
{
	//flip sun direction and no pisition
	vec3f sunDirection = sun * -1.f;
	//update shadow bounding box
	shadow_bbox.update();
	//build a sun Projection (width, height, length) which mean 10 10 40(-5,5,-5,5,-20,20)

	//replace shadow bounding box with player position
	//updateProjection(shadow_bbox.getWidth(), shadow_bbox.getHeight(), shadow_bbox.getLength());
	updateProjection(shadow_bbox.getWidth(),shadow_bbox.getHeight(),shadow_bbox.getWidth());
	//build a sun view matrix
	/*updateView(sunDirection, shadow_bbox.getCenter());*/
	updateView(sunDirection, shadow_bbox.getCenter());
	//finally we get sun projection view matrix
	projectionView = projection * view;

	//bind frame buffers and shader
	frameBuffer.bind();
	//cullface to front face when render framebuffer
	glCullFace(GL_FRONT);
	renderFrambuffer(entities);
	glCullFace(GL_BACK);
	frameBuffer.unbind();

}

void ShadowRenderer::renderFrambuffer(std::vector<entity_ptr>& entities)
{
	glUseProgram(depthShader);
	for (auto &e : entities)
	{
		Matrix4x4 model = e->transform();
		Matrix4x4 depthMVP = projectionView * model;
		ShaderTool::setUniformMatrix4f(depthShader, depthMVP, "depthMVP", true);

		glBindVertexArray(e->model.vao());
		glDrawElements(GL_TRIANGLES, e->model.indices_size(), GL_UNSIGNED_INT, NULL);
	}
	glBindVertexArray(0);
	glUseProgram(0);
}

void ShadowRenderer::updateProjection(float width, float height, float length)
{
	//reset light projection
	projection.setToIdentity();
	projection[0][0] = 2.f / width;
	projection[1][1] = 2.f / height;
	projection[2][2] = -2.f / length;
	projection[3][3] = 1.0f;
}

void ShadowRenderer::updateView(const vec3f &direction, const vec3f &center)
{
	vec3f dir = direction.normalized();
	vec3f centerPosition = center * -1.0f;
	view.setToIdentity();
	//get pitch
	float pitch = degree(acos(vec2f(dir.x, dir.z).length()));
	float yaw = degree(atan(dir.x / dir.z));

	yaw = dir.z > 0.0f ? yaw - 180 : yaw;
	view.rotate(AXIS::X, pitch);
	view.rotate(AXIS::Y, -yaw);
	view.translate(centerPosition);
}

GLuint ShadowRenderer::getShadowMap()
{
	return frameBuffer.shadowMap;
}

//to get shadow view projetion space for NDC texture coords
Matrix4x4 ShadowRenderer::getShadowMatrix()
{
	return  bias * projectionView;
}
