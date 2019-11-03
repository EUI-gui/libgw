#include "GWPainter.h"
#include <Windows.h>

GW::GWPainter::GWPainter(GWWidget* paintWidget) 
	:m_paintObejct(paintWidget->WinID())
{
	m_dc = (void*)GetDC(HWND(m_paintObejct));
	m_private = (void*)SelectObject(HDC(m_dc), m_pen.WinPen());
}

GW::GWPainter::GWPainter(const GWPen& pen, GWWidget* paintWidget)
{
	m_dc = (void*)GetDC(HWND(m_paintObejct));
	m_pen = pen;
	m_private = (void*)SelectObject(HDC(m_dc), m_pen.WinPen());
}

GW::GWPainter::~GWPainter()
{
	SelectObject(HDC(m_dc), m_private);
	ReleaseDC(HWND(m_paintObejct), HDC(m_dc));
}

void GW::GWPainter::save()
{
	m_dcObjects.push_back(GetDC(HWND(m_paintObejct)));
	SaveDC(HDC(m_dcObjects.back()));
}

void GW::GWPainter::restore()
{
	if (m_dcObjects.size() != 0)
	{
		RestoreDC(HDC(m_dcObjects.back()), -1);
		m_dcObjects.pop_back();
	}
}

void GW::GWPainter::drawRect(int x, int y, int width, int height)
{
	::Rectangle(HDC(m_dc), x, y, width, height);
}

void GW::GWPainter::drawRect(const GWRect& rect)
{
	drawRect(rect.x(), rect.y(), rect.width(), rect.height());
}

void GW::GWPainter::setPen(const GWPen& pen)
{
	m_pen = pen;
	m_private = (void*)SelectObject(HDC(m_dc), m_pen.WinPen());
}

GW::GWPen GW::GWPainter::getPen() const
{
	return m_pen;
}

//GW::GWPainter& GW::GWPainter::operator=(const GWPen& pen)
//{
//	return *this;
//}
