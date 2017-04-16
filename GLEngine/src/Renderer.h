#pragma once

#include <config.h>
#include <vector>
#include <Mesh.h>
#include <baserenderer.h>

class PlayerCamera;
class Renderer : public AbstractRenderer
{
public:
	Renderer();
	~Renderer();

	//condition
	bool isRunninig = false;

	//---------- pass OpenGL func  ----------
	void initialize();
	void render();
	void resize(uint32_t width, uint32_t height);
	//------------ View Matrix Camera for shaders ----------
	void init_view_matrix();
	void update_view_matrix();

	struct 
	{
		Matrix4x4 proj;
		Matrix4x4 text;
	}projection;

	PlayerCamera* camera;

private:
	//redner mode
	void render_forward();
	void render_terrian();
	void render_flat();

	void render_text();

};




