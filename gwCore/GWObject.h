#pragma once

#include <iostream>
#include <vector>

#include "GWMetaObject.h"

namespace GW
{
	class GWObjectPrivate;

	class GWPoint
	{
	public:
		int x;
		int y;
	};

	class GWRect
	{
	public:
		int x;
		int y;
		int width;
		int height;
	};

	class GW_CORE_EXPORT GWObject : public GWMetaObject
	{
	public:
		GWObject(GWObject* parent = nullptr);
		GWObject(std::string objectName, GWObject* parent = nullptr);
		virtual ~GWObject();

	public:
		std::string getObjectName();
		void setObjectName(std::string objectName);
		GWObject* getParent();

		void addChild(GWObject* child);
		void removeChild(GWObject* child);
	private:
		GWObjectPrivate* m_private;
	};
}
