#include "hzpch.h"
#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Hazel {
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		HZ_CORE_TRACE("{0}", e);
	}

	void Application::Run()
	{
		while (m_running)
		{
			glClearColor(1, 0, 0.5, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}
}