#include "entity.h"


Entity::Entity(const Model &model, const vec3f & pos, float rx, float ry, float rz, float scale)
	: model(model), m_position(pos), rot_x(rx), rot_y(ry), rot_z(rz), m_scale(scale)
{

}

void Entity::translate(float x, float y, float z)
{

	m_position += vec3f(x, y, z);
}

void Entity::rotation(float x, float y, float z)
{
	rot_x += x;
	rot_y += y;
	rot_z += z;
}

Matrix4x4 Entity::transform() const
{
	Matrix4x4 matrix;
	matrix.translate(m_position);
	matrix.rotate(AXIS::X, rot_x);
	matrix.rotate(AXIS::Y, rot_y);
	matrix.rotate(AXIS::Z, rot_z);
	matrix.scale(m_scale);
	return matrix;
}

float Entity::get_texture_offset_x()
{
	//TODO	get offset of texture terrain
	
	return 0.0f;
}

float Entity::get_texture_offset_z()
{
	//TODO
	return 0.0f;
}

