#pragma once

#include <GL/glew.h>
#include <matrix4x4.h>
#include <vec2f.h>
#include <vec3f.h>
#include <entity.h>
#include <terrain.h>

#define PLAYER_GRAVITY		-10.f
#define PLAYER_RUN_SPEED	20.f
#define PLAYER_TURN_SPEED	150.f

class Renderer;
class PlayerCamera;
class Player : public Entity
{
public:
	using Entity::Entity;

	void render(Renderer* renderer);
	void moving(const Terrain &terrain);
	
	void input_state();
	void moving_forward();
	void moving_back();
	float distance = 10.f;

	float speed = 0.0f;
	float turn_speed = 0;
	float upward_speed = 0;
	bool on_air = false;

	Matrix4x4 matrix;
	PlayerCamera* camera;
};

