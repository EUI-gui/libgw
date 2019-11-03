#include "GWPen.h"
#include <Windows.h>
using namespace GW;

GW::GWPen::GWPen()
{
	m_format = Format(PS_SOLID);
	m_width = 1;
	m_color = GWColor(0,0,0);
	update();
}

GW::GWPen::GWPen(const GWPen& pen)
{
	*this = pen;
}

GW::GWPen::GWPen(GWColor color, int width, Format format)
{
	m_color = color;
	m_width = width;
	m_format = format;
	update();
}

inline void GW::GWPen::setWidth(int width)
{
	m_width = width;
	update();
}

inline int GW::GWPen::getWidth() const
{
	return m_width;
}

inline void GW::GWPen::setFormat(Format format)
{
	m_format = format;
	update();
}

inline GWPen::Format GW::GWPen::getFormat() const
{
	return m_format;
}

inline void GW::GWPen::setColor(GWColor color)
{
	m_color = color;
	update();
}

inline GWColor GW::GWPen::getColor() const
{
	return m_color;
}

void* GW::GWPen::WinPen()
{
	return m_pen;
}

GWPen& GW::GWPen::operator=(const GWPen& other)
{
	memcpy(this, &other, sizeof(GWPen));
	update();
	return *this;
}

void GW::GWPen::update()
{
	if(m_pen)  DeleteObject(HPEN(m_pen));
	m_pen = CreatePen(int(m_format), m_width, RGB(m_color.r(), m_color.g(), m_color.b()));
}
