#include "GWWidget.h"
#include "GWApplication.h"

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
};

int main(int argc, char*argv[])
{
	GWApplication app(argc,argv);

	Signaler signaler;

	slotWidget w(&app);
	w.show();

	GWObject::connect(&signaler, signaler.sig, &w, &slotWidget::sltfunc);

	signaler.emitSignal();

	return app.exec();
}