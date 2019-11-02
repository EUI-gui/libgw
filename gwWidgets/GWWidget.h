#pragma once

#include <GWObject.h>

namespace GW
{
	class GWWidgetPirvate;

	class GWWidget : public GWObject
	{
	public:
		enum windowType
		{
			GW_HIDE = 0,
			GW_NORMAL = 1,
			GW_MINIMIZED = 2,
			GW_MAXIMIZE = 3,
			GW_NOACTIVATE = 4,
			GW_SHOW = 5,
			GW_MINIMIZE = 6,
			GW_MINNOACTIVE = 7,
			GW_SHOWNA = 8,
			GW_RESTORE = 9,
			GW_SHOWDEFAULT = 10,
			GW_MAX = 11
		};
	public:
		GWWidget(GWObject* parent = nullptr);
		virtual ~GWWidget();

	public:
		void show(GWWidget::windowType type = GW_NORMAL);
		void hide();
		void close();
		GWPoint getPos();
	public:
		virtual void createEvent();
		virtual void showEvent();
		virtual void hideEvent();
		virtual void closeEvent();
		virtual void keyPressEvent(__int64 key);
		virtual void keyReleaseEvent(__int64 key);
		virtual void mousePressEvent(GWPoint point);
		virtual void mouseMoveEvent(GWPoint point);
		virtual void mouseReleaseEvent(GWPoint point);
		virtual void paintEvent();
		virtual void resizeEvent();
		virtual void moveEvent(GWPoint point);
		virtual void activateEvent();
		//virtual void wheelEvent();
	private:
		void create();
	private:
		GWWidgetPirvate* m_private;

		friend class GWWidgetPirvate;
	};
}
