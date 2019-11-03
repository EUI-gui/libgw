#ifndef GWMetaObject_H
#define GWMetaObject_H

#include <list>
#include "libgwdefs.h"

#define slots
#define signals public
#define emit 

namespace GW
{
	class GWMetaObjectPrivate;
	class GWMetaObject;
	template<typename T>
	class GWSlotFunctionBase;
	template<typename GWReceiver, typename GWReturn>
	class GWSlotFunction;
	template<typename T>
	class GWSignal;

	template<typename GWReturn, typename ...GWArgs>
	class  GWSlotFunctionBase<GWReturn(GWArgs...)>
	{
	public:
		explicit GWSlotFunctionBase(void* slot, GWMetaObject* receiver = nullptr)
			:m_receiver(receiver),
			m_slot(slot) {}
		GWMetaObject* getReceiver() { return m_receiver; }
		virtual void operator() (GWArgs&... args) = 0;

	private:
		void* m_slot;
		GWMetaObject* m_receiver;
		friend class GWMetaObject;
	};

	template<typename GWReceiver, typename GWReturn, typename ...GWArgs>
	class GWSlotFunction<GWReceiver, GWReturn(GWArgs...)> : public GWSlotFunctionBase<GWReturn(GWArgs...)>
	{
	public:
		typedef void (GWReceiver::* GWSlotPtr) (GWArgs...);

		GWSlotFunction(GWReceiver* receiver, GWSlotPtr slot)
			: GWSlotFunctionBase<GWReturn(GWArgs...)>((void*)&slot, (GWMetaObject*)receiver),
			m_slotfunc(slot) {}

	public:
		void operator() (GWArgs&... args)
		{
			(((GWReceiver*)GWSlotFunctionBase<GWReturn(GWArgs...)>::getReceiver())->*m_slotfunc) (args...);
		}

	private:
		GWSlotPtr m_slotfunc;
		friend class GWMetaObject;
	};

	template<typename GWReturn, typename... GWArgs>
	class  GWSignal<GWReturn(GWArgs...)>
	{
	public:
		void operator() (GWArgs... args)
		{
			for (auto iter = _slots.begin(); iter != _slots.end(); ++iter)
				(**iter)(args...);
		}
		~GWSignal()
		{
			for (auto _slot : _slots)
				delete _slot;
		}
	private:
		std::list<GWSlotFunctionBase<GWReturn(GWArgs...)>* >  _slots;
		friend class GWMetaObject;
	};

	class  GWSlot
	{
	public:
		explicit GWSlot(void* slot, GWMetaObject* receiver = nullptr)
			:m_receiver(receiver),
			m_slot(slot) {}
	public:
		bool operator==(const GWSlot& other) { return (other.m_slot == m_slot) && (other.m_receiver == m_receiver); }

	private:
		void* m_slot;
		GWMetaObject* m_receiver;
		
		friend class GWMetaObject;
		friend class GWReceiverFind;
	};

	class  GW_CORE_EXPORT GWMetaObject
	{
	public:
		explicit GWMetaObject();
		virtual ~GWMetaObject();

		template<class GWReceiver, typename ...GWArgs>
		static bool  connect(GWMetaObject* sender, GWSignal<void(GWArgs...)>& signal, GWReceiver* receiver, void (GWReceiver::* SlotFunc) (GWArgs...));

		template<class GWReceiver, typename ...GWArgs>
		static bool  disconnect(GWMetaObject* sender, GWSignal<void(GWArgs...)>& signal, GWReceiver* receiver, void (GWReceiver::* SlotFunc) (GWArgs...));

	private:
		static bool  __connect(GWMetaObject* sender, std::list<GWSlot*>* signal, GWMetaObject* receiver, void* slot);
		static bool  __disconnect(GWMetaObject* sender, std::list<GWSlot*>* signal, GWMetaObject* receiver, void* slot);
		void pushSignal(GWMetaObject* sender, std::list<GWSlot*>* signal);
		void freeSignal(GWMetaObject* sender, std::list<GWSlot*>* signal);
		void pushSlot(GWMetaObject* receiver);
		void freeSlot(GWMetaObject* receiver);
		void release();

	private:
		GWMetaObjectPrivate* m_private;
	};

	template<class GWReceiver, typename ...GWArgs>
	bool  GWMetaObject::connect(GWMetaObject* sender, GWSignal<void(GWArgs...)>& signal, GWReceiver* receiver, void (GWReceiver::* SlotFunc) (GWArgs...))
	{
		GWSlotFunction<GWReceiver, void(GWArgs...)>* _slotfunc = new GWSlotFunction<GWReceiver, void(GWArgs...)>(receiver, SlotFunc);
		return __connect(sender, reinterpret_cast<std::list<GWSlot*>*>(&(signal._slots)), (GWMetaObject*)receiver, (void*)_slotfunc);
	}

	template<class GWReceiver, typename ...GWArgs>
	bool  GWMetaObject::disconnect(GWMetaObject* sender, GWSignal<void(GWArgs...)>& signal, GWReceiver* receiver, void (GWReceiver::* SlotFunc) (GWArgs...))
	{
		return __disconnect(sender, reinterpret_cast<std::list<GWSlot*>*>(&(signal._slots)), (GWMetaObject*)receiver, (void*)&SlotFunc);
	}
}

#endif // GWMetaObject_H
