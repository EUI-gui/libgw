#pragma once

#include <iostream>
#include <vector>

#include "GWMetaObject.h"
#include "GWRect.h"

namespace GW
{
	class GWObjectPrivate;

	class GW_CORE_EXPORT GWObject : public GWMetaObject
	{
	public:
		GWObject(GWObject* parent = nullptr);
		GWObject(std::string objectName, GWObject* parent = nullptr);
		virtual ~GWObject();

	public:
		std::string getObjectName();
		void setObjectName(std::string objectName);
		void setParent(GWObject* object);
		GWObject* getParent();

		void addChild(GWObject* child);
		void removeChild(GWObject* child);
		std::vector<GWObject*> getChilds();
	private:
		GWObjectPrivate* m_private;
	};
}
