#pragma once

#include "Core.h"
#include "Window.h"

#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_window;
		bool m_running = true;

		LayerStack m_layerStack;
	};

	Application* CreateApplication();
}
