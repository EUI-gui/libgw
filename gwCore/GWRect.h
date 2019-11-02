#pragma once

#include <GWPoint.h>
#include <GWSize.h>

class GWRect
{
public:
	GWRect();
	GWRect(const GWPoint& topleft, const GWPoint& bottomright);
	GWRect(const GWPoint& topleft, const GWSize& size);
	GWRect(int left, int top, int width, int height);
	GWRect(const GWRect& point);
	virtual ~GWRect();

public:
	inline int x() const;
	inline int y() const;

private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};

