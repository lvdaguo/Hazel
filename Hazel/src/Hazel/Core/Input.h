#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"

namespace Hazel {
	/// <summary>
	/// 静态类，轮询输入
	/// 内部实现为单例
	/// </summary>
	class Input
	{
	protected:
		Input() = default;
		virtual ~Input() = default;

	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static bool IsKeyPressed(KeyCode keycode) { return s_instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(MouseCode button) { return s_instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		static Scope<Input> Create();

	private:
		static Scope<Input> s_instance;
	};

}