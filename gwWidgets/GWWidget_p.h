#pragma once
#include "GWObject.h"

#include <Windows.h>
#include <map>

namespace GW
{
	class GWWidgetPirvate : public GWObject
	{
	public:

		GWWidgetPirvate(GWObject* parent);
		virtual ~GWWidgetPirvate();
		

		void init();
	public:
		HINSTANCE hInstance = nullptr;
		bool m_register = false;
		HWND m_hwnd;
		int m_type;
		GWObject* m_parent;
	private:
		std::string RegisterWnd();
		HWND CreateWnd(std::string className);
	};
}

