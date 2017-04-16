#pragma once

#include <Model.h>
#include <vec3f.h>

class Entity
{
public:
	Entity(
		Model& model,
		const vec3f& pos,
		float rx, float ry, float rz, float scale = 1.0f);

	//not input states just depend on while loop frame time
	void translate(float x, float y, float z);
	void rotation(float x, float y, float z);

	float get_texture_offset_x();
	float get_texture_offset_z();

	Model model;

	vec3f& position()  { return m_position; }
	float get_rot_x() { return rot_x; }
	float get_rot_y() { return rot_y; }
	float get_rot_z() { return rot_z; }
	float get_scale() { return scale; }

private:
	vec3f m_position;
	float rot_x = 0.0f;
	float rot_y = 0.0f;
	float rot_z = 0.0f;
	float scale;
};