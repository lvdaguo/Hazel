#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {

	// 当前事件都为阻塞，当事件触发时，立刻执行订阅函数
	// 更好的方法是将事件缓冲，在update的某一阶段一次性全部处理

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	// 事件抽象基类
	class Event
	{
		friend class EventDispatcher;
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		bool IsHandled() const { return Handled; }

		bool Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_event(event) { }

		template <typename T, typename F>
		bool Dispatch(F func)
		{
			if (m_event.GetEventType() == T::GetStaticType())
			{
				// 向下转换event， 调用func
				m_event.Handled = func(static_cast<T&>(m_event));
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};

	// 使事件可以用Log打印出来
	inline std::ostream& operator << (std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}