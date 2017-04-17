#pragma once

#include <GL/glew.h>
#include <matrix4x4.h>
#include <vec2f.h>
#include <vec3f.h>
#include <entity.h>
#include <terrain.h>

#define PLAYER_GRAVITY			-50.f//-50.f
#define PLAYER_RUN_SPEED		20.f//20.f
#define PLAYER_TURN_SPEED		160.f
#define PLAYER_JUMP_INTENSITY	30.f;

class Renderer;
class PlayerCamera;
class Player : public Entity
{
public:
	using Entity::Entity;

	void render(Renderer &renderer);
	void moveProcess(const Terrain &terrain);

	void setCamera(PlayerCamera& camera) { m_camera = &camera; }
	PlayerCamera& camera() { return *m_camera; }
	float debug_height = 0.f;
private:
	void inputStateEvent();
	void jump();
	void moving_forward();
	void moving_back();
	float distance = 10.f;

	float currentRunSpeed = 0.0f;
	float curruntTurnSpeed = 0;
	float currentUpwardSpeed = 0;
	bool on_air = false;

	Matrix4x4 matrix;
	PlayerCamera* m_camera;
};

