#include "camera.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL.h>

Camera::Camera(Player &player)
	: m_player(player)
{
	player.setCamera(*this);
}

void Camera::moveProcess()
{
	calcZoom();
	calcPitch();
	calcAngle();
	float H_distance = distanceFromPlayer * cos(radians(m_pitch));
	float V_distance = distanceFromPlayer * sin(radians(m_pitch));
	calcPosition(H_distance, V_distance);
	m_yaw = 180 - (m_player.ry() + angleAroundPlayer);
}

void Camera::calcZoom()
{
	float zoom_level = mouse_wheel_delta;
	distanceFromPlayer -= zoom_level;
	mouse_wheel_delta = 0;
}

void Camera::calcPitch()
{
	if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK)
	{
		float pitch_delta = mouse_y_delta;
		m_pitch += pitch_delta;
		mouse_y_delta = 0; //reset
	}
}

void Camera::calcAngle()
{
	if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK)
	{
		//vertical
		float angle_chagne = mouse_x_delta;
		angleAroundPlayer -= angle_chagne;
		mouse_x_delta = 0;
	}
}

void Camera::calcPosition(float hori_distance, float vert_distance)
{
	//get y rotation theta
	float theta_rotation = m_player.ry() + angleAroundPlayer;
	float x_offset = hori_distance * sin(radians(theta_rotation));
	float z_offset = hori_distance * cos(radians(theta_rotation));
	m_position.x = m_player.position().x - x_offset;		//invert from player
	m_position.y = m_player.position().y + vert_distance;	// y doset not need
	m_position.z = m_player.position().z - z_offset;
}

Matrix4x4 Camera::viewMatrix()
{
	//player Camera view matrix
	Matrix4x4 view;
	view.rotate(AXIS::X, pitch());
	view.rotate(AXIS::Y, yaw());
	vec3f center = -position() - vec3f(0, 3, 0);
	view.translate(center);
	return view;
}

void Camera::mouseMoveEvent(int x, int y)
{
	mouse_x_delta = 0.3 * x;
	mouse_y_delta = 0.3 * y;
}


void Camera::mouseWheelEvent(int delta)
{
	mouse_wheel_delta = delta;
}

void Camera::setProjection(float fovy, float aspect, float znear, float zfar)
{
	this->m_fovy = fovy;
	this->m_aspect = aspect;
	this->m_nearPlane = znear;
	this->m_farPlane = zfar;
	projection = vml::perspective(fovy, aspect, znear, zfar);
}

const Matrix4x4& Camera::projectionMatrix() const
{
	return projection;
}

