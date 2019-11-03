#include "GWWidget.h"

#include <Windows.h>
#include <functional>  
#include <map>
#include "GWWidget_p.h"

using namespace GW;



GWWidget::GWWidget(GWObject* parent) : GWObject(parent)
{
	createEvent();
	create();
}

GWWidget::~GWWidget()
{
}

void GW::GWWidget::show(GWWidget::windowType type)
{
	if (m_private->m_register)
	{
		ShowWindow(m_private->m_hwnd, type);
		UpdateWindow(m_private->m_hwnd);
	}
}

void GW::GWWidget::hide()
{
	if (m_private->m_register)
	{
		ShowWindow(m_private->m_hwnd, GW_HIDE);
		UpdateWindow(m_private->m_hwnd);
	}
}

void GW::GWWidget::close()
{
	PostMessage(this->m_private->m_hwnd, WM_DESTROY, 0, 0);
	CloseWindow(m_private->m_hwnd);
}

void GW::GWWidget::update()
{
	if (m_private->m_hwnd)
	{
		//SendMessage(this->m_private->m_hwnd, WM_PAINT,0,0);
		RECT clientRect = { 0 };
		GetClientRect(m_private->m_hwnd, &clientRect);
		InvalidateRect(m_private->m_hwnd,&clientRect,false);
		UpdateWindow(m_private->m_hwnd);
	}
}

GWRect GW::GWWidget::rect() const
{
	RECT rect = {0};
	::GetClientRect(HWND(WinID()), &rect);
	return GWRect(rect.left, rect.top, rect.right, rect.bottom);
}

void GW::GWWidget::setParent(GWWidget* parent)
{
	GWObject::setParent(parent);
	::SetParent(HWND(this->WinID()), HWND(parent->WinID()));
}

GWWidget* GW::GWWidget::getParent()
{
	return dynamic_cast<GWWidget*>(GWObject::getParent());
}

GWPoint GW::GWWidget::pos()
{
	if (dynamic_cast<GWWidget*>(this->getParent()))
	{
		return GWPoint();
	}
	else
	{
		RECT rect = { 0 };
		GetWindowRect(m_private->m_hwnd, &rect);
		return GWPoint(rect.left, rect.top);
	}
}

void GW::GWWidget::resize(int width, int height)
{
	GWPoint pos = this->pos();
	MoveWindow(m_private->m_hwnd, pos.x(), pos.y(), width, height, true);
}

void GW::GWWidget::resize(GWSize size)
{
	return resize(size.width(), size.height());
}

void* GW::GWWidget::WinID() const
{
	return this->m_private->m_hwnd;
}

void GW::GWWidget::createEvent()
{
	
}

void GW::GWWidget::showEvent()
{
	
}

void GW::GWWidget::hideEvent()
{
	
}

void GW::GWWidget::closeEvent()
{
	
}

void GW::GWWidget::keyPressEvent(__int64 key)
{
	
}

void GW::GWWidget::keyReleaseEvent(__int64 key)
{
	
}

void GWWidget::create()
{
	m_private = new GWWidgetPirvate(this);
	m_private->init();
}

void GW::GWWidget::mouseMoveEvent(GWPoint point)
{
}

void GW::GWWidget::mouseReleaseEvent(GWPoint point)
{
}

void GW::GWWidget::mousePressEvent(GWPoint point)
{
}

void GW::GWWidget::paintEvent()
{
	RECT rect = { 0 };
	GetClientRect(m_private->m_hwnd, &rect);

	HDC dc = GetDC(m_private->m_hwnd);
	Rectangle(dc, rect.left, rect.top, rect.right, rect.bottom);

	ReleaseDC(m_private->m_hwnd,dc);

	std::cout << this << ":paintEvent" << endl;
}

void GW::GWWidget::resizeEvent()
{
}

void GW::GWWidget::moveEvent(GWPoint point)
{
}

void GW::GWWidget::activateEvent()
{
}
