#pragma once
#include <iostream>

class GWSize
{
public:
	GWSize();
	GWSize(int width, int height);
	GWSize(const GWSize& point);

public:
	inline int width() const;
	inline int height() const;
	inline void setX(int width);
	inline void setY(int height);

public:
	inline bool operator==(const GWSize& p);
	inline bool operator!=(const GWSize& p);

	inline const GWSize operator+(const GWSize& p);
	inline GWSize& operator+=(const GWSize& p);

	inline const GWSize operator-(const GWSize& p);
	inline GWSize& operator-=(const GWSize& p);

	inline const GWSize operator*(const GWSize& p);
	inline GWSize& operator*=(const GWSize& p);

	inline const GWSize operator/(const GWSize& p);
	inline GWSize& operator/=(const GWSize& p);

	friend std::ostream& operator<< (std::ostream& out, const GWSize& p);
private:
	int m_width;
	int m_height;
};

