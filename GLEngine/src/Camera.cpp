#include "Camera.h"



Camera::Camera(vec3f pos, vec3f up, float yaw, float pitch)
	: front(vec3f(0,0,-1.f)), movement_speed(SPEED), mouseSensivity(SENSIVITY), zoom(ZOOM)
{
	this->pos = pos;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	update();
}


Camera::~Camera()
{
}

Matrix4x4 Camera::view()
{
	return vml::lookAt(pos, pos + front, up);
}

void Camera::process_keyboard(Camera_Movement direction, float deltaTime)
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

void Camera::process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch)
{
	xoffset *= this->mouseSensivity;
	yoffset *= this->mouseSensivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrain_pitch)
	{
		if (this->pitch > 89.0f)
			this->pitch = 89.0f;
		if (this->pitch < -89.0f)
			this->pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->update();
}

void Camera::process_mouse_scroll(float yoffset)
{
	if (this->zoom >= 1.0f && this->zoom <= 45.0f)
		this->zoom -= yoffset;
	if (this->zoom <= 1.0f)
		this->zoom = 1.0f;
	if (this->zoom >= 45.0f)
		this->zoom = 45.0f;
}

void Camera::update()
{
	vec3f front;
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));
	this->front = front.normalized();
	
	this->right = vec3f::cross(this->front, this->worldUp).normalized();  
	this->up = vec3f::cross(this->right, this->front).normalized();
}

	/*-----------------------------------------------------*/

VkCamera::VkCamera(float fov, float aspect, float znear, float zfar)
{
	this->fov = fov;
	this->aspect = aspect;
	this->znear = znear;
	this->zfar = zfar;
	
	proj = vml::perspective(fov, aspect, znear, zfar);
}

void VkCamera::update_view()
{
	Matrix4x4 rot_mat;
	Matrix4x4 trans_mat;

	rot_mat.rotate(AXIS::X, rot.x);
	rot_mat.rotate(AXIS::Y, rot.y);
	rot_mat.rotate(AXIS::Z, rot.z);

	trans_mat.translate(pos);

	view = rot_mat * trans_mat;
}

void VkCamera::update_aspect_ratio(float aspect)
{
	this->aspect = aspect;
	proj = vml::perspective(fov, this->aspect, znear, zfar);
}

void VkCamera::set_position(const vec3f &position)
{
	this->pos = position;
	update_view();
}

void VkCamera::set_rotation(const vec3f &rotation)
{
	this->rot = rotation;
	update_view();
}

void VkCamera::rotate(const vec3f &delta)
{
	this->rot += delta;
	update_view();
}

void VkCamera::set_translate(const vec3f &translate)
{
	this->pos = translate;
	update_view();
}

void VkCamera::translate(const vec3f &delta)
{
	this->pos += delta;
	update_view();
}

void VkCamera::update(float delta)
{
	vec3f front;
	front.x = -cos(radians(rot.x)) * sin(radians(rot.y));
	front.y = sin(radians(rot.x));
	front.z = cos(radians(rot.x)) * cos(radians(rot.y));
	front.normalize();

	float move_speed = delta * speed.move;

	if (keys.up)
		pos += front * move_speed;
	if (keys.down)
		pos -= front * move_speed;
	if (keys.up)
		pos -= vec3f::cross(front, vec3f(0, 1, 0)).normalized() * move_speed;
	if (keys.up)
		pos += vec3f::cross(front, vec3f(0, 1, 0)).normalized() * move_speed;

	update_view();
}
