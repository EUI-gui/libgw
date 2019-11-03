#include <GWMetaObject.h>
#include <string>
#include <algorithm>

namespace GW
{
	class SIGNALS
	{
	public:
		SIGNALS(GWMetaObject* _sender, std::list<GWSlot*>* _signal)
			:sender(_sender), signal(_signal) { }
		bool operator==(const SIGNALS& r) const { return r.sender == sender && r.signal == signal; }
	public:
		GWMetaObject* sender;
		std::list<GWSlot*>* signal;
	};

	class GWReceiverFind
	{
	public:
		GWReceiverFind(GWMetaObject* receiver) :m_receiver(receiver) {}
		bool operator() (GWSlot*& other) { return other->m_receiver == this->m_receiver; }
		bool operator() (GWMetaObject* receiver) { return this->m_receiver == receiver; }
	private:
		GWMetaObject* m_receiver;
	};

	class GWSenderFind
	{
	public:
		GWSenderFind(GWMetaObject* s) :sender(s) {}
		bool operator() (SIGNALS& other) { return other.sender == sender; }
	private:
		GWMetaObject* sender;
	};

	class GWMetaObjectPrivate
	{
	public:
		~GWMetaObjectPrivate()
		{
			m_signals.clear();
			m_senders.clear();
		}

		std::list<SIGNALS>  m_signals;
		std::list<GWMetaObject*>  m_senders;
	};

	GWMetaObject::GWMetaObject()
		:m_private(new GWMetaObjectPrivate)
	{
	}

	GWMetaObject::~GWMetaObject()
	{
		release();
		delete m_private;
	}

	void GWMetaObject::pushSignal(GWMetaObject* sender, std::list<GWSlot*>* signal)
	{
		SIGNALS sp(sender, signal);
		m_private->m_signals.push_back(sp);
	}

	void GWMetaObject::freeSignal(GWMetaObject* sender, std::list<GWSlot*>* signal)
	{
		m_private->m_signals.remove(SIGNALS(sender, signal));
	}

	void GWMetaObject::release()
	{
		for (auto signaIter = m_private->m_signals.begin(); signaIter != m_private->m_signals.end(); signaIter++)
		{
			auto signal = signaIter->signal;
			signaIter->signal->remove_if(GWReceiverFind(this));
			signaIter->sender->m_private->m_senders.remove_if(GWReceiverFind(this));
		}

		for (auto senderIter = m_private->m_senders.begin(); senderIter != m_private->m_senders.end(); senderIter++)
		{
			GWMetaObject* receiver = *senderIter;
			receiver->m_private->m_signals.remove_if(GWSenderFind(this));
		}
	}

	void GWMetaObject::pushSlot(GWMetaObject* receiver)
	{
		m_private->m_senders.push_front(receiver);
	}

	void GWMetaObject::freeSlot(GWMetaObject* receiver)
	{
		std::list<GWMetaObject*>::iterator it = std::find(m_private->m_senders.begin(), m_private->m_senders.end(), receiver);
		if (it == m_private->m_senders.end()) return;
		m_private->m_senders.erase(it);
	}

	bool GWMetaObject::__connect(GWMetaObject* sender, std::list<GWSlot*>* signal, GWMetaObject* receiver, void* slot)
	{
		if (sender == 0 || receiver == 0 || signal == 0 || slot == 0) return false;

		GWSlot* m_slot = (GWSlot*)slot;

		void* funcptr = 0;
		void* _funcptr = 0;
		memcpy(&funcptr, m_slot->m_slot, sizeof(void*));
		memcpy(&_funcptr, funcptr, sizeof(void*));

		for (auto sig : *signal)
		{
			if (*((GWSlot*)slot) == *sig)
			{
				return false;
			}
		}

		signal->push_back(m_slot);
		sender->pushSlot(receiver);
		receiver->pushSignal(sender, signal);

		return true;
	}

	bool GWMetaObject::__disconnect(GWMetaObject* sender, std::list<GWSlot*>* signal, GWMetaObject* receiver, void* slot)
	{
		bool _b = false;

		if (sender == 0 || receiver == 0 || signal == 0 || slot == 0) return _b;

		std::list< GWSlotFunction<GWMetaObject, void(void)>* >* SlotFunctionType = (std::list<GWSlotFunction<GWMetaObject, void(void)>*>*)signal;

		void* funcptr = 0;
		memcpy(&funcptr, slot, sizeof(void*));

		for (auto iter = signal->begin(); iter != signal->end(); iter++)
		{
			auto _funcType = SlotFunctionType->begin();
			void* savePtr = 0;
			memcpy(&savePtr, &((*_funcType)->m_slotfunc),sizeof(void*));

			if (savePtr == funcptr)
			{
				auto freePtr = *iter;
				delete (freePtr);
				signal->erase(iter);
				break;
			}
			_funcType++;
		}
		sender->freeSlot(receiver);
		receiver->freeSignal(sender, signal);
		return _b;
	}

}

