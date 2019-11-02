#include "GWSize.h"

GWSize::GWSize() : m_width(0), m_height(0)
{
}

GWSize::GWSize(int width, int height) : m_width(width), m_height(height)
{
}

GWSize::GWSize(const GWSize& point) : m_width(point.width()), m_height(point.height())
{
}

int GWSize::width() const
{
	return 0;
}

int GWSize::height() const
{
	return 0;
}

void GWSize::setX(int x)
{
	m_width = x;
}

void GWSize::setY(int y)
{
	m_height = y;
}

inline bool GWSize::operator==(const GWSize& p)
{
	if (p.width() == m_width && p.height() == m_height)
		return true;
	return false;
}

inline bool GWSize::operator!=(const GWSize& p)
{
	if (p.width() != m_width || p.height() != m_height)
		return true;
	return false;
}

inline const GWSize GWSize::operator+(const GWSize& p)
{
	return GWSize(m_width + p.width(), m_height + p.height());
}

inline GWSize& GWSize::operator+=(const GWSize& p)
{
	m_width += p.width();
	m_height += p.height();
	return *this;
}

inline const GWSize GWSize::operator-(const GWSize& p)
{
	return GWSize(m_width - p.width(), m_height - p.height());
}

inline GWSize& GWSize::operator-=(const GWSize& p)
{
	m_width -= p.width();
	m_height -= p.height();
	return *this;
}

inline const GWSize GWSize::operator*(const GWSize& p)
{
	return GWSize(m_width * p.width(), m_height * p.height());
}

inline GWSize& GWSize::operator*=(const GWSize& p)
{
	m_width *= p.width();
	m_height *= p.height();
	return *this;
}

inline const GWSize GWSize::operator/(const GWSize& p)
{
	return GWSize(m_width / p.width(), m_height / p.height());
}

inline GWSize& GWSize::operator/=(const GWSize& p)
{
	m_width /= p.width();
	m_height /= p.height();
	return *this;
}

std::ostream& operator<<(std::ostream& out, const GWSize& p)
{
	out << "GWSize(x: " << p.width() << ", y: " << p.height() << ")";
	return out;
}
