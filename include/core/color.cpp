#include <Color.h>

const Color Color::black	= Color(   0,   0,   0);
const Color Color::white	= Color(   1,   1,   1);
const Color Color::red		= Color(   1,   0,   0);
const Color Color::yellow	= Color(   1,   1,   0);
const Color Color::error	= Color(   1,   0,   1);
const Color Color::null		= 0;

Color Color::clamp(const Color &c, float min, float max)
{
	float r, g, b;
	r = std::max(min, std::min(max, c.r));
	g = std::max(min, std::min(max, c.g));
	b = std::max(min, std::min(max, c.b));
	return Color(r, g, b);
}

Color Color::gamma(const Color &c, float gamma)
{
	float g = 1.0f / gamma;
	return Color(std::max(0.0f, std::min(1.0f, std::pow(c.r, g))),
				std::max(0.0f, std::min(1.0f, std::pow(c.g, g))), 
				std::max(0.0f, std::min(1.0f, std::pow(c.b, g))));
}