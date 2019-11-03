#include "GWColor.h"

using namespace GW;

static const GWColor global_colors[] = {
		GWColor(255, 255, 255), // Qt::color0
		GWColor(0,   0,   0), // Qt::color1
		GWColor(0,   0,   0), // black
		GWColor(255, 255, 255), // white
		GWColor(128, 128, 128), // index 248   medium gray
		GWColor(160, 160, 164), // index 247   light gray
		GWColor(192, 192, 192), // index 7     light gray
		GWColor(255,   0,   0), // index 249   red
		GWColor(0, 255,   0), // index 250   green
		GWColor(0,   0, 255), // index 252   blue
		GWColor(0, 255, 255), // index 254   cyan
		GWColor(255,   0, 255), // index 253   magenta
		GWColor(255, 255,   0), // index 251   yellow
		GWColor(128,   0,   0), // index 1     dark red
		GWColor(0, 128,   0), // index 2     dark green
		GWColor(0,   0, 128), // index 4     dark blue
		GWColor(0, 128, 128), // index 6     dark cyan
		GWColor(128,   0, 128), // index 5     dark magenta
		GWColor(128, 128,   0), // index 3     dark yellow
};

GWColor::GWColor() : m_r(0), m_g(0), m_b(0), m_a(255)
{
}

GWColor::GWColor(int r, int g, int b, int a) 
	: m_r(r), m_g(g), m_b(b), m_a(a)
{
}

GW::GWColor::GWColor(GlobalColor color)
{
	*this = global_colors[int(color)];
}

GWColor::~GWColor()
{
}

inline void GW::GWColor::setR(int r)
{
	m_r = r;
}

inline const int GW::GWColor::r() const
{
	return m_r;
}

inline void GW::GWColor::setG(int g)
{
	m_g = g;
}

inline const int GW::GWColor::g() const
{
	return m_g;
}

inline void GW::GWColor::setB(int b) 
{
	m_b = b;
}

inline const int GW::GWColor::b() const
{
	return m_b;
}

inline void GW::GWColor::setA(int a)
{
	m_a = a;
}

inline const int GW::GWColor::a() const
{
	return m_a;
}

bool GW::GWColor::operator==(const GWColor& other)
{
	return (m_r && other.r()) && (m_g && other.g()) && (m_b && other.b()) && (m_a && other.a());
}
