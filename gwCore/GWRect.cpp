#include "GWRect.h"

GWRect::GWRect() : m_x(0), m_y(0), m_width(0), m_height(0)
{
}

GWRect::GWRect(const GWPoint& topleft, const GWPoint& bottomright) 
	: m_x(topleft.x()), m_y(topleft.y()), m_width(bottomright.x() - topleft.x()), m_height(bottomright.y() - topleft.y())
{
}

GWRect::GWRect(const GWPoint& topleft, const GWSize& size)
	: m_x(topleft.x()), m_y(topleft.y()), m_width(size.width()), m_height(size.height())
{
}

GWRect::GWRect(int left, int top, int width, int height)
	: m_x(left), m_y(top), m_width(width), m_height(height)
{

}

GWRect::GWRect(const GWRect& point) 
	: m_x(point.x()), m_y(point.y()), m_width(point.width()), m_height(point.height())
{
}

inline int GWRect::x() const
{
	return m_x;
}

inline int GWRect::y() const
{
	return m_y;
}

inline int GWRect::width() const
{
	return m_width;
}

inline int GWRect::height() const
{
	return m_height;
}

inline bool GWRect::operator==(const GWRect& p)
{
	return ((p.x() == m_x) && (p.y() == m_y) && (p.width() == m_width) && (p.height() == m_height));
}

inline bool GWRect::operator!=(const GWRect& p)
{
	return ((p.x() != m_x) && (p.y() != m_y) && (p.width() != m_width) && (p.height() != m_height));
}

inline const GWRect GWRect::operator+(const GWRect& p)
{
	return GWRect(m_x +p.x(), m_y+p.y(), m_width + p.width(), m_height + p.height());
}

inline GWRect& GWRect::operator+=(const GWRect& p)
{
	m_x += p.x();
	m_y += p.y();
	m_width += p.width();
	m_height += p.height();
	return *this;
}

inline const GWRect GWRect::operator-(const GWRect& p)
{
	return GWRect(m_x-p.x(), m_y-p.y(), m_width-p.width(), m_height-p.height());
}

inline GWRect& GWRect::operator-=(const GWRect& p)
{
	m_x -= p.x();
	m_y -= p.y();
	m_width -= p.width();
	m_height -= p.height();
	return *this;
}

inline const GWRect GWRect::operator*(const GWRect& p)
{
	return GWRect(m_x * p.x(), m_y * p.y(), m_width * p.width(), m_height * p.height());
}

inline GWRect& GWRect::operator*=(const GWRect& p)
{
	m_x *= p.x();
	m_y *= p.y();
	m_width *= p.width();
	m_height *= p.height();
	return *this;
}

inline const GWRect GWRect::operator/(const GWRect& p)
{
	return GWRect(m_x / p.x(), m_y / p.y(), m_width / p.width(), m_height / p.height());
}

inline GWRect& GWRect::operator/=(const GWRect& p)
{
	m_x /= p.x();
	m_y /= p.y();
	m_width /= p.width();
	m_height /= p.height();
	return *this;
}
