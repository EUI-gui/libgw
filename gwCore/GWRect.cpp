#include "GWRect.h"

GWRect::GWRect() : m_x(0), m_y(0), m_width(0), m_height(0)
{
}

GWRect::GWRect(const GWPoint& topleft, const GWPoint& bottomright) 
	: m_x(topleft.x()), m_y(topleft.y()), m_width(bottomright.x() - topleft.x()), m_height(bottomright.y() - topleft.y())
{
}

GWRect::GWRect(const GWPoint& topleft, const GWSize& size)
	: m_x(topleft.x()), m_y(topleft.y()), m_width(size.x()), m_height(size.y())
{
}

GWRect::GWRect(int left, int top, int width, int height)
	: m_x(left), m_y(top), m_width(width), m_height(height)
{

}

GWRect::GWRect(const GWRect& point)
{
}

GWRect::~GWRect()
{
}

inline int GWRect::x() const
{
	return 0;
}

inline int GWRect::y() const
{
	return 0;
}
