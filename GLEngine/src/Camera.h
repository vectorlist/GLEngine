#pragma once

#include <vec3f.h>
#include <vec3f.h>
#include <matrix4x4.h>
#include <vml.h>

#define YAW			-90.f
#define PITCH		0.0f
#define SPEED		3.0f
#define SENSIVITY	0.25f
#define ZOOM		45.f

enum Camera_Movement
{
	FORWARD = 0,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera(vec3f pos = vec3f(0), vec3f up = vec3f(0,1,0),
		float yaw = YAW, float pitch = PITCH);
	~Camera();

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

	/*--------------------------------------------------------*/

struct Camera_key
{
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
};

class VkCamera 
{
public:
	VkCamera(float fov, float aspect, float znear, float zfar);
	float fov;
	float znear,zfar;
	float aspect;

	void update_view();
	void update_aspect_ratio(float aspect);

	vec3f rot;
	vec3f pos;

	Matrix4x4 proj;
	Matrix4x4 view;

	Camera_key keys;

	struct 
	{
		float rot = 1.0f;
		float move = 1.0f;
	}speed;

	void set_position(const vec3f &position);
	void set_rotation(const vec3f &rotation);
	void rotate(const vec3f &delta);
	void set_translate(const vec3f &translate);
	void translate(const vec3f &delta);

	void update(float delta);
};