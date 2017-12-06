#pragma once

#include <GL/glew.h>
#include <vec2f.h>
#include <vec3f.h>
#include <ft2build.h>
#include <map>

#include <vml.h>
#include <matrix4x4.h>

#include FT_FREETYPE_H

enum Text_Type
{
	TEXT_SCREEN = 0U,
	TEXT_OBJECT
};

struct Font
{
	GLuint texture;
	vec2i size;
	vec2i bearing;
	GLuint advance;
};

class Text
{
public:
	Text(const std::string fontPath, uint32_t fontSize);
	~Text();
	
	GLuint vao, vbo;
	std::string font_path;
	uint32_t font_size;

	void initialize();
	void buildBuffer();

	void render(
		GLuint shader,
		const std::string &text,
		float x, 
		float y,
		float scale,
		const vec3f &color);

	bool enable = true;
	Text_Type type = TEXT_SCREEN;
	//to ref
	Matrix4x4* proj;
private:
	std::map<GLchar, Font> fonts;
};

