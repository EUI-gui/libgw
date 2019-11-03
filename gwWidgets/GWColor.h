#pragma once

namespace GW
{
	class GWColor
	{
	public:
		enum GlobalColor { white = 3, black = 2, red = 7, darkRed = 13, green = 8, darkGreen = 14,
						   blue = 9, darkBlue = 15, cyan = 10, darkCyan = 16, magenta = 11, darkMagenta = 17,
						   yellow = 12, darkYellow = 18, gray = 5, darkGray = 4, lightGray = 6, 
						   color0 = 0, color1 = 1};
	public:
		GWColor();
		GWColor(int r, int g, int b, int a = 255);
		GWColor(GlobalColor color);
		~GWColor();

	public:
		inline void setR(int r);
		inline const int r() const;

		inline void setG(int g);
		inline const int g() const;

		inline void setB(int b);
		inline const int b() const;

		inline void setA(int a);
		inline const int a() const;

	public:
		bool operator==(const GWColor& other);
	private:
		int m_r;
		int m_g;
		int m_b;
		int m_a;
	};
}



