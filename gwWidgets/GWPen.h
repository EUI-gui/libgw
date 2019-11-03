#pragma once
#include "GWColor.h"

namespace GW
{
	class GWPen
	{
		enum class Format
		{
			SOLID,			/* straight line  */
			DASH,			/* -------  */
			DOT,			/* .......  */
			DASHDOT,		/* _._._._  */
			DASHDOTDOT,     /* _.._.._  */
		};
	public:
		GWPen();
		GWPen(const GWPen& pen);
		GWPen(GWColor color, int width = 1, Format format = Format::SOLID);

	public:
		inline void setWidth(int width);
		inline int getWidth() const;

		inline void setFormat(Format format);
		inline Format getFormat() const;

		inline void setColor(GWColor color);
		inline GWColor getColor() const;

		void* WinPen();

	public:
		GWPen& operator=(const GWPen& other);

	private:
		void update();
	private:
		void* m_pen;
		int m_width;
		GWColor m_color;
		Format m_format;
	};
}
