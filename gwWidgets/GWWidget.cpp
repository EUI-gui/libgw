#include "GWWidget.h"

#include <Windows.h>
#include <functional>  
#include <map>

using namespace GW;

static std::map<HWND, GWWidget*> __widgetMap;

// Callback function of window message
LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	GWWidget* __widget = nullptr;
	for (auto iter = __widgetMap.begin(); iter != __widgetMap.end(); iter++)
	{
		if (iter->first == hWnd)
			__widget = iter->second;
	}

	if(!__widget)
		return DefWindowProc(hWnd, nMsg, wParam, lParam);

	switch (nMsg)
	{
	case WM_CLOSE:
	{
		__widget->hide();
		__widget->hideEvent();
		return false;
	}
	case WM_DESTROY:
	{
		__widget->closeEvent();
		break;
	}
	case WM_QUIT:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_PAINT:
	{
		__widget->paintEvent();
		break;
	}
	case WM_SIZE:
	{
		__widget->resizeEvent();
		break;
	}
	case WM_ACTIVATE:
	{
		__widget->activateEvent();
		break;
	}
	case WM_MOVE:
	{
		GWPoint point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		__widget->moveEvent(point);
		break;
	}
	case WM_MOUSEMOVE:
	{
		GWPoint point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		__widget->mouseMoveEvent(point);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		GWPoint point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		__widget->mousePressEvent(point);
		break;
	}
	case WM_LBUTTONUP:
	{
		GWPoint point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		__widget->mouseReleaseEvent(point);
		break;
	}
	case WM_KEYDOWN:
	{
		__widget->keyPressEvent(lParam);
		break;
	}
	case WM_KEYUP:
	{
		__widget->keyReleaseEvent(lParam);
		break;
	}
	case SW_HIDE:
	{
		__widget->hideEvent();
		break;
	}
	case WM_SHOWWINDOW:
	{
		__widget->showEvent();
		break;
	}
	}
	return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

class GW::GWWidgetPirvate : public GWObject
{
public:
	
	GWWidgetPirvate(GWObject* parent)
		: GWObject(parent){}
	~GWWidgetPirvate()
	{ 
		if (m_hwnd)
		{
			CloseWindow(m_hwnd);
		}
	}

	void init();
public:
	HINSTANCE   hInstance;
	bool m_register = false;
	HWND m_hwnd;
	int m_type;
private:
	
	void RegisterWnd();
	HWND CreateWnd();
};

void GW::GWWidgetPirvate::init()
{
	m_type = GW::GWWidget::GW_NORMAL;
	RegisterWnd();
	m_hwnd = CreateWnd();
	__widgetMap[m_hwnd] = dynamic_cast<GW::GWWidget*>(this->getParent());
}

void GW::GWWidgetPirvate::RegisterWnd()
{
	WNDCLASSEX wcx = { 0 };
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hIcon = NULL;
	wcx.hIconSm = NULL;
	wcx.hInstance = hInstance;
	wcx.lpfnWndProc = WindowProc;

	wcx.lpszClassName = "Widget"; 
	wcx.lpszMenuName = NULL;
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom = RegisterClassEx(&wcx);
	if (nAtom == 0) m_register = false;
	else m_register = true;
}

HWND GW::GWWidgetPirvate::CreateWnd()
{
	HWND hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
		"Widget",
		"",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	return hWnd;
}

GWWidget::GWWidget(GWObject* parent) : GWObject(parent)
{
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

GWPoint GW::GWWidget::getPos()
{
	if (dynamic_cast<GWWidget*>(this->getParent()))
	{

	}
	else
	{
		GWPoint point;
		RECT rect = { 0 };
		GetWindowRect(m_private->m_hwnd, &rect);
		point.x = rect.left;
		point.y = rect.top;
		return point;
	}
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
	createEvent();
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
