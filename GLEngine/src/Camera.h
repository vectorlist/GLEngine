#pragma once

#include <vec3f.h>
#include <vec3f.h>
#include <matrix4x4.h>
#include <vml.h>
#include <Renderer.h>
#include <player.h>

#define YAW			-90.f
#define PITCH		0.0f
#define SPEED		2.f
#define SENSIVITY	0.25f
#define ZOOM		45.f

enum Camera_Movement
{
	FORWARD = 0,
	BACKWARD,
	LEFT,
	RIGHT
};

class PerspectiveCamera
{
public:
	PerspectiveCamera(vec3f pos = vec3f(0), vec3f up = vec3f(0,1,0),
		float yaw = YAW, float pitch = PITCH);
	~PerspectiveCamera();

	/*SHARE FUNC*/

	vec3f pos;
	vec3f front;
	vec3f up;
	vec3f right;
	vec3f worldUp;

	float yaw;
	float pitch;

	float mouseSensivity;
	float movement_speed;
	float zoom;

	Matrix4x4 view();
	void process_keyboard(Camera_Movement direction, float deltaTime);
	void process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch = true);
	void process_mouse_scroll(float yoffset);
private:
	void update();
};


class PlayerCamera
{
public:
	PlayerCamera(Player &player);


	/*SHARE FUNC*/
	void mouse_wheel(int delta);
	void mouse_move(int x, int y);
	void move();
	//get view matrix
	Matrix4x4 get_view_matirx();
	Player &player;
	//calc func
	void calc_zoom();
	void calc_pitch();
	void calc_angle_around_player();
	void calc_camera_position(float hori, float vert);
	//motion
	

	vec3f position() { return m_position; }
	float get_pitch() { return pitch; }
	float get_yaw() { return yaw; }
private:

	float pitch = 0.0f;
	float yaw = 0.f;
	float roll = 0.0f;
	float distance_from_player = 25.f;
	float angle_around_player = 0.0f;
	int mouse_wheel_delta = 0; 
	int mouse_x_delta = 0;
	int mouse_y_delta = 0;
	vec3f m_position;

};