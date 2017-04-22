#pragma once

#include <Model.h>
#include <vec3f.h>

class Entity
{
public:
	Entity(
		const Model& model,
		const vec3f& pos,
		float rx, float ry, float rz, float scale = 1.0f);

	//not input states just depend on while loop frame time
	void translate(float x, float y, float z);
	void rotation(float x, float y, float z);

	float get_texture_offset_x();
	float get_texture_offset_z();

	const Model &model;

	vec3f& position()  { return m_position; }
	float rx() { return rot_x; }
	float ry() { return rot_y; }
	float rz() { return rot_z; }
	float scale() { return m_scale; }

private:
	vec3f m_position;
	float rot_x = 0.0f;
	float rot_y = 0.0f;
	float rot_z = 0.0f;
	float m_scale;
};

typedef std::shared_ptr<Entity> entity_ptr;