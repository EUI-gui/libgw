#include "GWApplication.h"
#include <Windows.h>
GW::GWApplication::GWApplication(int argc, char** argv)
{
}

GW::GWApplication::~GWApplication()
{
}

int GW::GWApplication::exec()
{
	int msgR = true;
	MSG nMsg = { 0 };

	while (msgR)
	{
		msgR = GetMessage(&nMsg, NULL, 0, 0);
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
	return msgR;
}
