#include "text.h"
#include <config.h>
#include <shadertool.h>

Text::Text(const std::string fontPath, uint32_t fontSize)
	: font_path(fontPath), font_size(fontSize)
{
	initialize();
}

Text::~Text()
{

}

void Text::initialize()
{
	FT_Library ft_lib;
	FT_Face face;

	if (FT_Init_FreeType(&ft_lib)) {
		LOG_ERROR("failed to init freetype.");
	}
	if (FT_New_Face(ft_lib, font_path.c_str(), 0, &face)) {
		LOG_ERROR("failed to create face font.");
	}
	
	FT_Set_Pixel_Sizes(face, 0, font_size);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
		LOG_ERROR("failed to load Glyph");

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; ++c) 
	{

		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			//skip if c empty
			continue;
		}

		auto& bitmap = face->glyph->bitmap;

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		//GL_RED for 1byte 0 - 255
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//build a new font object
		//@params : texture , (w/h) , (t/b), advance
		Font font = {
			texture,
			vec2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			vec2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		fonts.insert(std::pair<GLchar, Font>(c, font));
	}	//end of char loop

	glBindTexture(GL_TEXTURE_2D, NULL);
	FT_Done_Face(face);
	FT_Done_FreeType(ft_lib);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Text::buildBuffer()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	/*---------------- vao bounding -------------------*/
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);	//dynamic

	glEnableVertexAttribArray(0);				//layout =0
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);    //not sure 
	glBindVertexArray(NULL);
	/*------------------ vao finish --------------------*/

}

//shader used already outside
void Text::render(
	GLuint shader,
	const std::string &text,
	float x,
	float y,
	float scale,
	const vec3f &color)
{
	
	ShaderTool::setUniForm3f(shader, color, "text_color");
	//bounding vao
	glActiveTexture(GL_TEXTURE0); //use 0 for text only
	/*------------------- vao bounding --------------------*/
	glBindVertexArray(vao);

	
	for(auto &c : text)
	{
		auto &font = fonts[c];

		float xpos = x + font.bearing.x * scale;
		float ypos = y - (font.size.y - font.bearing.y) * scale;

		float w = font.size.x * scale;
		float h = font.size.y * scale;

		if (c == ' ') {

			int g = 10;
		}

		//vertex for plane with uv
		float vertices[6][4] = {
			{ xpos ,  ypos + h , 0.0f,0.0f },				//1 tri
			{ xpos ,  ypos     , 0.0f,1.0f },
			{ xpos + w,  ypos , 1.0f,1.0f },

			{ xpos ,    ypos + h , 0.0f,0.0f },				//2 tri
			{ xpos + w, ypos     , 1.0f,1.0f },
			{ xpos + w, ypos + h , 1.0f,0.0f }
		};

		//bind texture
		glBindTexture(GL_TEXTURE_2D, font.texture);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		//dynamic
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		
		//unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (font.advance >> 6) * scale;
	}

	glBindVertexArray(0);
	/*------------------ - vao finish --------------------*/
	glBindTexture(GL_TEXTURE_2D, 0);
}
