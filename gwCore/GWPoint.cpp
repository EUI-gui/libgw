#include "GWPoint.h"

GWPoint::GWPoint() : m_x(0), m_y(0)
{
}

GWPoint::GWPoint(int x, int y) : m_x(x), m_y(y)
{
}

GWPoint::GWPoint(const GWPoint& point) : m_x(point.x()), m_y(point.y())
{
}

int GWPoint::x() const 
{
	return 0;
}

int GWPoint::y() const
{
	return 0;
}

void GWPoint::setX(int x)
{
	m_x = x;
}

void GWPoint::setY(int y)
{
	m_y = y;
}

inline bool GWPoint::operator==(const GWPoint& p)
{
	if (p.x() == m_x && p.y() == m_y)
		return true;
	return false;
}

inline bool GWPoint::operator!=(const GWPoint& p)
{
	if (p.x() != m_x || p.y() != m_y)
		return true;
	return false;
}

inline const GWPoint GWPoint::operator+(const GWPoint& p)
{
	return GWPoint(m_x + p.x(), m_y + p.y());
}

inline GWPoint& GWPoint::operator+=(const GWPoint& p)
{
	m_x += p.x();
	m_y += p.y();
	return *this;
}

inline const GWPoint GWPoint::operator-(const GWPoint& p)
{
	return GWPoint(m_x - p.x(), m_y - p.y());
}

inline GWPoint& GWPoint::operator-=(const GWPoint& p)
{
	m_x -= p.x();
	m_y -= p.y();
	return *this;
}

inline const GWPoint GWPoint::operator*(const GWPoint& p)
{
	return GWPoint(m_x * p.x(), m_y * p.y());
}

inline GWPoint& GWPoint::operator*=(const GWPoint& p)
{
	m_x *= p.x();
	m_y *= p.y();
	return *this;
}

inline const GWPoint GWPoint::operator/(const GWPoint& p)
{
	return GWPoint(m_x/p.x(), m_y/p.y());
}

inline GWPoint& GWPoint::operator/=(const GWPoint& p)
{
	m_x /= p.x();
	m_y /= p.y();
	return *this;
}

std::ostream& operator<<(std::ostream& out, const GWPoint& p)
{
	out << "GWPoint(x: " << p.x() << ", y: " << p.y() << ")";
	return out;
}
