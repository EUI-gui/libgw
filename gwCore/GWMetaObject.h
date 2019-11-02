#ifndef GWMetaObject_H
#define GWMetaObject_H

#include <list>
#include <stdio.h>
#include "libgwdefs.h"

using namespace std;

class GWMetaObjectPrivate;
class GWMetaObject;

#define slots
#define signals public
#define emit 

template<typename No>
class GWSlotAPI;
template<typename Ret, typename ...Args>
class  GWSlotAPI<Ret(Args...)>
{
public:
	explicit GWSlotAPI(void* slot, GWMetaObject* receiver = NULL)
		:m_receiver(receiver),
		m_slot(slot)
	{
	}
	virtual ~GWSlotAPI() {}
	virtual void operator() (Args&... args) = 0;

private:
	GWSlotAPI& operator= (const GWSlotAPI&) = delete;

public:
	bool operator==(const GWSlotAPI& other)
	{
		return other.m_slot == m_slot && other.m_receiver == m_receiver;
	}

public:
	GWMetaObject* m_receiver;
protected:
	void* m_slot;
};

template<typename Receiver, typename No>
class GWSlotCpp;
template<typename Receiver, typename Ret, typename ...Args>
class GWSlotCpp<Receiver, Ret(Args...)> : public GWSlotAPI<Ret(Args...)>
{
public:
	typedef void (Receiver::* SlotFuncType) (Args...);

	GWSlotCpp(Receiver* r, SlotFuncType slot)
		: GWSlotAPI<Ret(Args...)>((void*)&slot, (GWMetaObject*)r),
		m_class_slot(slot)
	{
	}

	virtual ~GWSlotCpp() {}

public:
	void operator() (Args&... args)
	{
		(((Receiver*)GWSlotAPI<Ret(Args...)>::m_receiver)->*m_class_slot) (args...);
	}

private:
	SlotFuncType m_class_slot;
};


template<typename No>
class GWSignal;
template<typename Ret, typename... Args>
class  GWSignal<Ret(Args...)>
{
public:
	typedef list<GWSlotAPI<Ret(Args...)>* > SlotLstType;

public:
	void __emit(Args... args)
	{
		for (auto it = _slotLst.begin(); it != _slotLst.end(); ++it)
		{
			(*(*it)) (args...);
		}
	}

	void operator() (Args... args)
	{
		for (auto it = _slotLst.begin(); it != _slotLst.end(); ++it)
		{
			(*(*it)) (args...);
		}
	}

public:
	SlotLstType  _slotLst;
};


class  GWSlot
{
public:
	explicit GWSlot(void* slot, GWMetaObject* receiver = NULL)
		:m_receiver(receiver),
		m_slot(slot)
	{
	}
	virtual ~GWSlot() {}
	virtual void operator() (const GWSlot&);

private:
	GWSlot& operator= (const GWSlot&) = delete;

public:
	bool operator==(const GWSlot& other)
	{
		return other.m_slot == m_slot
			&& other.m_receiver == m_receiver;
	}

public:
	GWMetaObject* m_receiver;
protected:
	void* m_slot;
};

#define SIGNAL_TYPE(SlotFuncType)  list<GWSlot*>
#define SIGNAL_POINTER(SlotFuncType)  list<GWSlot*>*
#define SIGNAL_TYPE_ITERATOR(SlotFuncType)  list<GWSlot*>::iterator


class  GW_CORE_EXPORT GWMetaObject
{
signals:

	GWSignal<void(void)> sigDestroyed;

private:
	GWMetaObjectPrivate* m_priv;

public:
	explicit GWMetaObject(const char* name = NULL);
	GWMetaObject(const GWMetaObject& src);
	GWMetaObject& operator= (const GWMetaObject& src);
	virtual ~GWMetaObject();

	template<class Receiver, typename ...Args>
	static int  connect(GWMetaObject* sender, GWSignal<void(Args...)>& signal, Receiver* receiver, void (Receiver::* SlotFunc) (Args...));

	template<class Receiver, typename ...Args>
	static int  disconnect(GWMetaObject* sender, GWSignal<void(Args...)>& signal, Receiver* receiver, void (Receiver::* SlotFunc) (Args...));
	const char* name() const;


private:
	static int  privConnect(GWMetaObject* sender, SIGNAL_POINTER(void*) signal, GWMetaObject* receiver, void* slot);
	static int  privDisconnect(GWMetaObject* sender, SIGNAL_POINTER(void*) signal, GWMetaObject* receiver, void* slot);
	void saveSenderPair(GWMetaObject* sender, SIGNAL_POINTER(void*) signal);
	void deleteSenderPair(GWMetaObject* sender, SIGNAL_POINTER(void*) signal);
	void destructAsReceiver();
	void destructAsSender();
	void saveReceiver(GWMetaObject* receiver);
	void deleteReceiver(GWMetaObject* receiver);
};

template<class Receiver, typename ...Args>
int  GWMetaObject::connect(GWMetaObject* sender, GWSignal<void(Args...)>& signal, Receiver* receiver, void (Receiver::* SlotFunc) (Args...))
{
	GWSlotCpp<Receiver, void(Args...)>* vslot = new GWSlotCpp<Receiver, void(Args...)>(receiver, SlotFunc);
	int ret = privConnect(sender, reinterpret_cast<SIGNAL_POINTER(void*)>(&(signal._slotLst)), (GWMetaObject*)receiver, (void*)vslot);
	if (0 != ret)
	{
		delete vslot;
	}
	return ret;
}

template<class Receiver, typename ...Args>
int  GWMetaObject::disconnect(GWMetaObject* sender, GWSignal<void(Args...)>& signal, Receiver* receiver, void (Receiver::* SlotFunc) (Args...))
{
	int ret = privDisconnect(sender, reinterpret_cast<SIGNAL_POINTER(void*)>(&(signal._slotLst)), (GWMetaObject*)receiver, static_cast<void*>(&SlotFunc));
	return ret;
}

#endif // GWMetaObject_H
