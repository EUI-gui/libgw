#include "GWWidget.h"
#include "GWWidget_p.h"

using namespace GW;

std::map<HWND, GWWidget*> __widgetMap;

// Callback function of window message
LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	GWWidget* __widget = nullptr;
	for (auto iter = __widgetMap.begin(); iter != __widgetMap.end(); iter++)
	{
		if (iter->first == hWnd)
			__widget = iter->second;
	}

	if (!__widget)
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

GW::GWWidgetPirvate::GWWidgetPirvate(GWObject* parent) : GWObject(parent), m_parent(parent)
{
}

GW::GWWidgetPirvate::~GWWidgetPirvate()
{
	if (m_hwnd)
	{
		CloseWindow(HWND(m_hwnd));
	}
}

void GW::GWWidgetPirvate::init()
{
	m_type = GW::GWWidget::GW_NORMAL;
	m_hwnd = CreateWnd(RegisterWnd());
	GW::GWWidget* _widget = dynamic_cast<GW::GWWidget*>(m_parent);
	__widgetMap[HWND(m_hwnd)] = _widget;

	if (m_parent->getParent())
	{
		GW::GWWidget* parentwidget = dynamic_cast<GW::GWWidget*>(m_parent->getParent());
		if (parentwidget)
		{
			SetWindowLong(HWND(this->m_hwnd), GWL_EXSTYLE, WS_EX_TOOLWINDOW);
			//SetParent(HWND(this->m_hwnd), HWND(parentwidget->WinID()));
		}
	}
}

std::string GW::GWWidgetPirvate::RegisterWnd()
{
	char className[256] = { 0 };
	if (__widgetMap.size() == 0)
		sprintf_s(className, "%s", "Widget");
	else
		sprintf_s(className, "%s%d", "Widget", int(__widgetMap.size() + 1));

	WNDCLASSEX wcx = { 0 };
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hIcon = NULL;
	wcx.hIconSm = NULL;
	wcx.hInstance = HINSTANCE(hInstance);
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
			HINSTANCE(hInstance),
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
			HINSTANCE(hInstance),
			NULL);
	}
	return hWnd;
}