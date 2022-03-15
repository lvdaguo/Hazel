#pragma once

#include "Core.h"
#include "Window.h"

#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};

	Application* CreateApplication();
}
