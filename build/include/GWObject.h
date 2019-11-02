#pragma once

#include <iostream>
#include <vector>
#include "libgwdefs.h"

#include "GWMetaObject.h"

namespace GW
{
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
		std::vector<GWObject*> m_childs;
		std::string m_objectName;
		GWObject* m_parent;
	};
}


