#pragma once

#include "Core.h"
#include "Window.h"

#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"

// Application为单例，其持有的窗口对象也只有一个实例

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_window; }
		inline static Application& Get() { return *s_instance; }

	private:
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imguiLayer;

		bool m_running = true;

		LayerStack m_layerStack;

		static Application* s_instance;
	};

	Application* CreateApplication();
}
