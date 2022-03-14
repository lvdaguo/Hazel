#include "hzpch.h"
#include "WindowsWindow.h"

namespace Hazel {

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_data.Title = props.Title;
		m_data.Width = props.Width;
		m_data.Height = props.Height;

		static bool GLFWInitialized = false;

		HZ_CORE_INFO("Creating window {0}, ({1}, {2})\n", props.Title, props.Width, props.Height);
		if (GLFWInitialized == false)
		{
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initilize GLFW!");
			GLFWInitialized = true;
		}

		m_window = glfwCreateWindow(int(props.Width), int(props.Height), m_data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) glfwSwapInterval(1);
		else         glfwSwapInterval(0);
		m_data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_data.VSync;
	}
};