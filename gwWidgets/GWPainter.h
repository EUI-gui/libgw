#pragma once
#include "GWWidget.h"
#include "GWPen.h"
#include "GWRect.h"

namespace GW
{
	class GWPainter
	{
	public:
		GWPainter(GWWidget* paintWidget);
		GWPainter(const GWPen& pen, GWWidget* paintWidget);
		virtual ~GWPainter();

	public:
		void save();
		void restore();

	public:
		void drawRect(int x, int y, int width, int height);
		void drawRect(const GWRect& rect);

	public:
		void setPen(const GWPen& pen);
		GWPen getPen() const;
	//private:
	//	GWPainter& operator=(const GWPen& pen);

	private:
		void* m_paintObejct;
		void* m_dc;
		void* m_private;
		GWPen m_pen;
		std::vector<void*> m_dcObjects;
	};
}

