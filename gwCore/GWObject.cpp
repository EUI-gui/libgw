#include "GWObject.h"

using namespace GW;

class GW::GWObjectPrivate
{
public:
	std::vector<GWObject*> m_childs;
	std::string m_objectName;
	GWObject* m_parent;
};

GWObject::GWObject(GWObject* parent)
{
	m_private = new GWObjectPrivate();

	if (parent) parent->addChild(this);
	m_private->m_parent = parent;
}

GWObject::GWObject(std::string objectName, GWObject* parent)
{
	m_private = new GWObjectPrivate();

	m_private->m_objectName = objectName;
	if (parent) parent->addChild(this);
	m_private->m_parent = parent;
}

GWObject::~GWObject()
{
	for (GWObject* child : m_private->m_childs)
	{
		delete child;
	}
	delete m_private;
}

std::string GWObject::getObjectName()
{
	return m_private->m_objectName;
}

void GWObject::setObjectName(std::string objectName)
{
	m_private->m_objectName = objectName;
}

void GW::GWObject::setParent(GWObject* object)
{
	GWObject* _parent = this->getParent();
	if (_parent)
	{
		_parent->removeChild(this);
	}
	object->addChild(this);
}

void GWObject::addChild(GWObject* child)
{
	this->m_private->m_childs.push_back(child);
}

void GW::GWObject::removeChild(GWObject* child)
{
	for (auto iter = this->m_private->m_childs.begin(); iter != this->m_private->m_childs.end(); iter++)
	{
		if (*iter == child)
			this->m_private->m_childs.erase(iter);
	}
}

std::vector<GWObject*> GW::GWObject::getChilds()
{
	return m_private->m_childs;
}

GWObject* GW::GWObject::getParent()
{
	return this->m_private->m_parent;
}

