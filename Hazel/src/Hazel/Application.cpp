#include "hzpch.h"
#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Hazel {

	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (true)
		{
			glClearColor(1, 0, 0.5, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}
	}
}