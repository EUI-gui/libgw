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
		//__widget->update();
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
		//GWWidget* parentwidget = dynamic_cast<GWWidget*>(__widget->getParent());
		//if (parentwidget)
		//{
		//	SendMessage(HWND(parentwidget->WinID()), WM_PAINT, 0, 0);
		//}
		__widget->update();
		__widget->moveEvent(GWPoint(LOWORD(lParam), HIWORD(lParam)));
		break;
	}
	case WM_MOUSEMOVE:
	{
		//__widget->update();
		__widget->mouseMoveEvent(GWPoint(LOWORD(lParam), HIWORD(lParam)));
		break;
	}
	case WM_LBUTTONDOWN:
	{
		__widget->update();
		__widget->mousePressEvent(GWPoint(LOWORD(lParam), HIWORD(lParam)));
		break;
	}
	case WM_LBUTTONUP:
	{
		__widget->update();
		__widget->mouseReleaseEvent(GWPoint(LOWORD(lParam), HIWORD(lParam)));
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
		__widget->update();
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
		: GWObject(parent), m_parent(parent){}
	~GWWidgetPirvate()
	{ 
		if (m_hwnd)
		{
			CloseWindow(m_hwnd);
		}
	}

	void init();
public:
	HINSTANCE   hInstance = nullptr;
	bool m_register = false;
	HWND m_hwnd;
	int m_type;
	GWObject* m_parent;
private:
	std::string RegisterWnd();
	HWND CreateWnd(std::string className);
};

void GW::GWWidgetPirvate::init()
{
	m_type = GW::GWWidget::GW_NORMAL;
	m_hwnd = CreateWnd(RegisterWnd());
	GW::GWWidget* _widget = dynamic_cast<GW::GWWidget*>(m_parent);
	__widgetMap[m_hwnd] = _widget;

	if (m_parent->getParent())
	{
		GW::GWWidget* parentwidget = dynamic_cast<GW::GWWidget*>(m_parent->getParent());
		if (parentwidget)
		{
			SetWindowLong(this->m_hwnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW);
			//SetParent(this->m_hwnd, HWND(parentwidget->WinID()));
		}	
	}
	
}

std::string GW::GWWidgetPirvate::RegisterWnd()
{
	char className[256] = { 0 };
	if (__widgetMap.size() == 0)
		sprintf_s(className, "%s", "Widget");
	else
		sprintf_s(className, "%s%d", "Widget", int(__widgetMap.size()+1));

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

	wcx.lpszClassName = className;
	wcx.lpszMenuName = NULL;
	wcx.style = 0;// CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom = RegisterClassEx(&wcx);
	if (nAtom == 0) m_register = false;
	else m_register = true;

	return std::string(className);
}

HWND GW::GWWidgetPirvate::CreateWnd(std::string className)
{
	HWND hWnd;
	
	GWWidget* parentwidget = dynamic_cast<GWWidget*>(m_parent->getParent());

	if (!parentwidget)
	{
		hWnd = CreateWindowEx(/*WS_EX_CLIENTEDGE*/0,
			className.c_str(),
			"",
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			hInstance,
			NULL);
	}
	else
	{
		hWnd = CreateWindow(/*0,*/
			className.c_str(),
			"",
			WS_CHILDWINDOW | WS_VISIBLE | BS_DEFPUSHBUTTON,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			HWND(parentwidget->WinID()),
			NULL,
			hInstance,
			NULL);
	}
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

void* GW::GWWidget::WinID()
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
