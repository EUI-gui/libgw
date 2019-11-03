#include "GWWidget.h"
#include "GWApplication.h"
#include "GWPainter.h"

using namespace GW;

class Signaler : public GWObject
{
signals:
	GWSignal<void(int)> sig;
public:
	void emitSignal()
	{
		std::cout << "emit signal" << std::endl;
		emit sig(1);
	}
};

class slotWidget : public GWWidget
{
public:
	slotWidget(GWObject* parent = nullptr) : GWWidget(parent) {}

public slots:
	void sltfunc(int a)
	{
		std::cout << "this is a slot function." <<std::endl;
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

	GWObject::connect(&signaler, signaler.sig, &w2, &slotWidget::sltfunc);
	signaler.emitSignal();

	GWObject::disconnect(&signaler, signaler.sig, &w2, &slotWidget::sltfunc);
	signaler.emitSignal();

	return app.exec();
}