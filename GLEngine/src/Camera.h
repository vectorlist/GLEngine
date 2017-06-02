#pragma once

#include <vec3f.h>
#include <vec3f.h>
#include <matrix4x4.h>
#include <vml.h>
#include <Renderer.h>
#include <player.h>

class Camera
{
public:
	Camera(Player &player);

	void moveProcess();
	void mouseMoveEvent(int x, int y);
	void mouseWheelEvent(int delta);
	
	void setProjection(float fovy, float apsect, float znear, float zfar);
	const Matrix4x4& projectionMatrix() const;
	Matrix4x4 viewMatrix();
	
	Player& player() { return m_player; }
	vec3f& position() { return m_position; }
	float pitch() { return m_pitch; }
	float yaw() { return m_yaw; }
	float fov() const { return m_fovy; }
	float aspect() const { return m_aspect; }
	float nearPlane() const { return m_nearPlane; }
	float farPlane() const { return m_farPlane; }
private:
	void calcZoom();
	void calcPitch();
	void calcAngle();
	void calcPosition(float hori, float vert);

	float m_pitch = 0.0f;
	float m_yaw = 0.f;
	float roll = 0.0f;
	float distanceFromPlayer = 22.f;
	float angleAroundPlayer = 0.0f;
	int mouse_wheel_delta = 0; 
	int mouse_x_delta = 0;
	int mouse_y_delta = 0;
	vec3f m_position;
	Player &m_player;
	//projection
	Matrix4x4 projection;
	float m_fovy;
	float m_aspect;
	float m_nearPlane;
	float m_farPlane;
};

