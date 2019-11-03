#include "GWWidget.h"
#include "GWApplication.h"
#include <windows.h>
#include "GWPainter.h"
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
		GWPainter painter(this);
		painter.save();
		{
			painter.setPen(GWPen(GWColor::GlobalColor::red, 5));
			painter.drawRect(this->rect());
		}
		painter.restore();

		std::cout << this << ":paintEvent:вс" << endl;
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