#include "camera.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL.h>


PerspectiveCamera::PerspectiveCamera(vec3f pos, vec3f up, float yaw, float pitch)
	: front(vec3f(0,0,-1.f)), movement_speed(SPEED), mouseSensivity(SENSIVITY), zoom(ZOOM)
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

			/*PLAYER*/

PlayerCamera::PlayerCamera(Player &player)
	: player(player)
{
	player.camera = this;
}

void PlayerCamera::calc_zoom()
{
	float zoom_level = mouse_wheel_delta;
	distance_from_player -= zoom_level;
	mouse_wheel_delta = 0;
}

void PlayerCamera::calc_pitch()
{
	if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK)
	{
		//calc degree angle player to camera
		float pitch_change = mouse_y_delta;
		pitch += pitch_change;
		mouse_y_delta = 0; //reset
	}
}

void PlayerCamera::calc_angle_around_player()
{
	if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK)
	{
		//vertical
		float angle_chagne = mouse_x_delta;
		angle_around_player -= angle_chagne;
		mouse_x_delta = 0;
	}
}

void PlayerCamera::calc_camera_position(float hori_distance, float vert_distance)
{
	//get y rotation theta
	float theta_rotation = player.get_rot_y() + angle_around_player;
	float x_offset = hori_distance * sin(radians(theta_rotation));
	float z_offset = hori_distance * cos(radians(theta_rotation));
	m_position.x = player.position().x - x_offset;		//invert from player
	m_position.y = player.position().y + vert_distance;	// y doset not need
	m_position.z = player.position().z - z_offset;
}

void PlayerCamera::move()
{
	// 1 .calc zom
	calc_zoom();
	calc_pitch();
	calc_angle_around_player();
	float horicontal_distance = distance_from_player * cos(radians(pitch));
	float vertical_distance = distance_from_player * sin(radians(pitch));
	calc_camera_position(horicontal_distance, vertical_distance);
	yaw = 180 - (player.get_rot_y() + angle_around_player);
}

Matrix4x4 PlayerCamera::get_view_matirx()
{
	//player Camera view matrix
	Matrix4x4 view;
	view.rotate(AXIS::X, get_pitch());
	view.rotate(AXIS::Y, get_yaw());
	view.translate(-position());
	return view;
}

//input
void PlayerCamera::mouse_wheel(int delta)
{
	mouse_wheel_delta = delta;
}

void PlayerCamera::mouse_move(int x, int y)
{
	mouse_x_delta = 0.3 * x;
	mouse_y_delta = 0.3 * y;
}
