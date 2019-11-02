#include <GWMetaObject.h>
#include <string>
#include <algorithm>

struct SenderPair
{
	SenderPair(GWMetaObject* _sender, SIGNAL_POINTER(void*) _signal)
		:sender(_sender), signal(_signal)
	{ }

	bool operator==(const SenderPair& r) const
	{
		return r.sender == sender && r.signal == signal;
	}

	GWMetaObject* sender;
	SIGNAL_POINTER(void*) signal;
};

class GWMetaObjectPrivate
{
public:
	GWMetaObjectPrivate(const char* nm) : strName(nm)
	{
		spLst.clear();
		rLst.clear();
	}

	~GWMetaObjectPrivate()
	{
		spLst.clear();
		rLst.clear();
	}

	string   strName;
	list<SenderPair>  spLst;
	list<GWMetaObject*>  rLst;
};

GWMetaObject::GWMetaObject(const char* n)
	:m_priv(new GWMetaObjectPrivate(NULL == n ? "" : n))
{
}

GWMetaObject::~GWMetaObject()
{
	destructAsReceiver();

	sigDestroyed();
	destructAsSender();

	delete m_priv;
}

void GWMetaObject::saveSenderPair(GWMetaObject* sender, SIGNAL_POINTER(void*) signal)
{
	SenderPair sp(sender, signal);
	m_priv->spLst.push_back(sp);
}

void GWMetaObject::deleteSenderPair(GWMetaObject* sender, SIGNAL_POINTER(void*) signal)
{
	m_priv->spLst.remove(SenderPair(sender, signal));
}

class Receiver_Is
{
public:
	GWMetaObject* receiver;

	bool operator( ) (GWSlot*& obj1)
	{
		return obj1->m_receiver == this->receiver;
	}

	bool operator( ) (GWMetaObject* receiver)
	{
		return this->receiver == receiver;
	}

	Receiver_Is(GWMetaObject* r)
		:receiver(r)
	{

	}
};

class Slot_Is_CppSlot
{
private:
	GWSlot vslot;

public:
	bool operator( ) (GWSlot*& obj1)
	{
		return vslot == *obj1;
	}

	Slot_Is_CppSlot(const GWSlot& s)
		:vslot(s)
	{
	}
};

int GWMetaObject::privConnect(GWMetaObject* sender, SIGNAL_POINTER(void*) signal, GWMetaObject* receiver, void* slot)
{
	if (sender == 0 || receiver == 0 || signal == 0 || slot == 0)
	{
		printf("can not connect %s::%p to %s::%p\n",
			sender ? sender->name() : "(null)",
			signal,
			receiver ? receiver->name() : "(null)",
			slot);
		return -1;
	}

	GWSlot* vslot = (GWSlot*)slot;
	SIGNAL_TYPE_ITERATOR(void*) it = std::find_if(signal->begin(), signal->end(), Slot_Is_CppSlot(*vslot));
	if (it != signal->end())
	{
		printf("already connected\n");
		return -2;
	}

	signal->push_back(vslot);

	sender->saveReceiver(receiver);

	receiver->saveSenderPair(sender, signal);

	return 0;
}

void GWMetaObject::destructAsReceiver()
{
	list<SenderPair >::iterator it = m_priv->spLst.begin();
	while (it != m_priv->spLst.end())
	{
		it->signal->remove_if(Receiver_Is(this));
		it->sender->m_priv->rLst.remove_if(Receiver_Is(this));
		++it;
	}
}

class Sender_Is
{
public:
	GWMetaObject* sender;

	bool operator( ) (SenderPair& obj1)
	{
		return obj1.sender == sender;
	}

	Sender_Is(GWMetaObject* s)
		:sender(s)
	{

	}
};

void GWMetaObject::destructAsSender()
{
	list<GWMetaObject*>::iterator it = m_priv->rLst.begin();
	while (it != m_priv->rLst.end())
	{
		GWMetaObject* receiver = *it;
		receiver->m_priv->spLst.remove_if(Sender_Is(this));
		++it;
	}
}

void GWMetaObject::saveReceiver(GWMetaObject* receiver)
{
	m_priv->rLst.push_front(receiver);
}

void GWMetaObject::deleteReceiver(GWMetaObject* receiver)
{
	list<GWMetaObject*>::iterator it = std::find(m_priv->rLst.begin(), m_priv->rLst.end(), receiver);
	if (it == m_priv->rLst.end())
	{
		return;
	}

	m_priv->rLst.erase(it);
}

int GWMetaObject::privDisconnect(GWMetaObject* sender, SIGNAL_POINTER(void*) signal, GWMetaObject* receiver, void* slot)
{
	if (sender == 0 || receiver == 0 || signal == 0 || slot == 0)
	{
		printf("can not disconnect sender %s::%p from receiver %s::%p\n",
			sender ? sender->name() : "(null)",
			signal,
			receiver ? receiver->name() : "(null)",
			slot);
		return -1;
	}

	SIGNAL_TYPE_ITERATOR(void*) it = std::find_if(signal->begin(), signal->end(), Slot_Is_CppSlot(GWSlot(slot, receiver)));
	if (it == signal->end())
	{
		return -2;
	}

	signal->erase(it);

	sender->deleteReceiver(receiver);

	receiver->deleteSenderPair(sender, signal);

	return 0;
}


const char* GWMetaObject::name() const
{
	return  m_priv->strName.c_str();
}

GWMetaObject& GWMetaObject::operator= (const GWMetaObject& /*src*/)
{
	return *this;
}

GWMetaObject::GWMetaObject(const GWMetaObject& /*src*/)
	:m_priv(new GWMetaObjectPrivate(""))
{
}
void GWSlot::operator() (const GWSlot&)
{
	printf("\n");
}
