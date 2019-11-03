#include "GWWidget.h"
#include "GWApplication.h"
#include <windows.h>
using namespace GW;

class Signaler : public GWObject
{
signals:
	GWSignal<void(const char*, int)> sig;

public:
	void emitSignal()
	{
		emit sig("libGW!", 1);
	}
};

class slotWidget : public GWWidget
{
public:
	slotWidget(GWObject* parent = nullptr) : GWWidget(parent) {}

public slots:
	void sltfunc(const char* msg, int number)
	{
		std::cout << "msg:" << msg << std::endl;
		std::cout << "number:" << number << endl;
	}
public:
	virtual void paintEvent()
	{
		RECT rect = { 0 };
		::GetClientRect(HWND(WinID()), &rect);

		HDC dc = GetDC(HWND(WinID()));
		HPEN newPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(dc, newPen);
		Rectangle(dc, rect.left, rect.top, rect.right, rect.bottom);

		ReleaseDC(HWND(WinID()), dc);
		SelectObject(dc, oldPen);
		std::cout << this << ":paintEvent:вс" << endl;
		//UpdateWindow(HWND(this->WinID()));
		
	}
};

int main(int argc, char*argv[])
{
	GWApplication app(argc,argv);

	Signaler signaler;

	GWWidget w(&app);
	w.show();

	slotWidget w2(&w);
	w2.resize(800,600);
	w2.show();

	GWObject::connect(&signaler, signaler.sig, &w2, &slotWidget::sltfunc);

	signaler.emitSignal();

	return app.exec();
}