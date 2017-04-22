#include <terrainrenderer.h>
#include <terrainshader.h>
#include <Mesh.h>
#include <terrain.h>
#include <texture.h>

TerrainRenderer::TerrainRenderer()
{
	//shader.bind();
	////terrainshader has uniform already by string
	//shader.bindTextureLocations();
	//shader.unbind();
}

TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::Render(const std::vector<terrain_ptr>& terrains)
{
	shader->bind();
	shader->bindTextureLocations();
	for (auto terrain : terrains)
	{
		Mesh &mesh = *terrain->mesh;
		shader->setModelMatrix(terrain->matrix);
		//each active texture 0---4 overhead
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, terrain->textures.background->id);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, terrain->textures.textureR->id);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, terrain->textures.textureG->id);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, terrain->textures.textureB->id);

		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, terrain->textures.textureBlend->id);

		glBindVertexArray(mesh.vao);
		glDrawElements(GL_TRIANGLES, mesh.indices_size, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(NULL);
		

	}

	/*for (uint32_t i = 0; i < 5; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, NULL);
	}*/
	shader->unbind();
	glBindVertexArray(0);
}
