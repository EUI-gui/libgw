#pragma once
#include <iostream>

class GWPoint
{
public:
	GWPoint();
	GWPoint(int x, int y);
	GWPoint(const GWPoint& point);

public:
	inline int x() const;
	inline int y() const;
	inline void setX(int x);
	inline void setY(int y);

public:
	inline bool operator==(const GWPoint& p);
	inline bool operator!=(const GWPoint& p);

	inline const GWPoint operator+(const GWPoint& p);
	inline GWPoint& operator+=(const GWPoint& p);

	inline const GWPoint operator-(const GWPoint& p);
	inline GWPoint& operator-=(const GWPoint& p);

	inline const GWPoint operator*(const GWPoint& p);
	inline GWPoint& operator*=(const GWPoint& p);

	inline const GWPoint operator/(const GWPoint& p);
	inline GWPoint& operator/=(const GWPoint& p);

	friend std::ostream& operator<< (std::ostream& out, const GWPoint& p);
private:
	int m_x;
	int m_y;
};

