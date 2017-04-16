#include "entity.h"


Entity::Entity(Model &model, const vec3f & pos, float rx, float ry, float rz, float scale)
	: model(model), m_position(pos), rot_x(rx), rot_y(ry), rot_z(rz), scale(scale)
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