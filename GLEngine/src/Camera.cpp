#include "camera.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL.h>

PlayerCamera::PlayerCamera(Player &player)
	: m_player(player)
{
	player.setCamera(*this);
}

void PlayerCamera::moveProcess()
{
	calcZoom();
	calcPitch();
	calcAngle();
	float H_distance = distanceFromPlayer * cos(radians(m_pitch));
	float V_distance = distanceFromPlayer * sin(radians(m_pitch));
	calcPosition(H_distance, V_distance);
	m_yaw = 180 - (m_player.get_rot_y() + angleAroundPlayer);
}

void PlayerCamera::calcZoom()
{
	float zoom_level = mouse_wheel_delta;
	distanceFromPlayer -= zoom_level;
	mouse_wheel_delta = 0;
}

void PlayerCamera::calcPitch()
{
	if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK)
	{
		float pitch_delta = mouse_y_delta;
		m_pitch += pitch_delta;
		mouse_y_delta = 0; //reset
	}
}

void PlayerCamera::calcAngle()
{
	if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK)
	{
		//vertical
		float angle_chagne = mouse_x_delta;
		angleAroundPlayer -= angle_chagne;
		mouse_x_delta = 0;
	}
}

void PlayerCamera::calcPosition(float hori_distance, float vert_distance)
{
	//get y rotation theta
	float theta_rotation = m_player.get_rot_y() + angleAroundPlayer;
	float x_offset = hori_distance * sin(radians(theta_rotation));
	float z_offset = hori_distance * cos(radians(theta_rotation));
	m_position.x = m_player.position().x - x_offset;		//invert from player
	m_position.y = m_player.position().y + vert_distance;	// y doset not need
	m_position.z = m_player.position().z - z_offset;
}

Matrix4x4 PlayerCamera::viewMatrix()
{
	//player Camera view matrix
	Matrix4x4 view;
	view.rotate(AXIS::X, pitch());
	view.rotate(AXIS::Y, yaw());
	vec3f center = -position() - vec3f(0, 3, 0);
	view.translate(center);
	return view;
}

void PlayerCamera::mouseMoveEvent(int x, int y)
{
	mouse_x_delta = 0.3 * x;
	mouse_y_delta = 0.3 * y;
}


void PlayerCamera::mouseWheelEvent(int delta)
{
	mouse_wheel_delta = delta;
}

//----------------- PERSPECTIVE CAMERA ---------------------

PerspectiveCamera::PerspectiveCamera(vec3f pos, vec3f up, float yaw, float pitch)
	: front(vec3f(0, 0, -1.f)), movement_speed(SPEED), mouseSensivity(SENSIVITY), zoom(ZOOM)
{
	this->pos = pos;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	update();
}


PerspectiveCamera::~PerspectiveCamera()
{
}

Matrix4x4 PerspectiveCamera::view()
{
	return vml::lookAt(pos, pos + front, up);
}

void PerspectiveCamera::process_keyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = this->movement_speed * deltaTime;
	if (direction == FORWARD)
		this->pos += this->front * velocity;
	if (direction == BACKWARD)
		this->pos -= this->front * velocity;
	if (direction == LEFT)
		this->pos -= this->right * velocity;
	if (direction == RIGHT)
		this->pos += this->right * velocity;
}

void PerspectiveCamera::process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch)
{
	xoffset *= this->mouseSensivity;
	yoffset *= this->mouseSensivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (constrain_pitch)
	{
		if (this->pitch > 89.0f)
			this->pitch = 89.0f;
		if (this->pitch < -89.0f)
			this->pitch = -89.0f;
	}
	this->update();
}

void PerspectiveCamera::process_mouse_scroll(float yoffset)
{
	if (this->zoom >= 1.0f && this->zoom <= 45.0f)
		this->zoom -= yoffset;
	if (this->zoom <= 1.0f)
		this->zoom = 1.0f;
	if (this->zoom >= 45.0f)
		this->zoom = 45.0f;
}

void PerspectiveCamera::update()
{
	vec3f front;
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));
	this->front = front.normalized();

	this->right = vec3f::cross(this->front, this->worldUp).normalized();
	this->up = vec3f::cross(this->right, this->front).normalized();
}