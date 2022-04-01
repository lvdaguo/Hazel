#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/Window.h"

#include "Hazel/Core/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/Core/Timestep.h"
#include "Hazel/ImGui/ImGuiLayer.h"

// Application为单例，其持有的窗口对象也只有一个实例

int main(int argc, char** argv);

namespace Hazel {
	class Application
	{
	public:
		Application(const std::string& name = "Hazel App");
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
		Window& GetWindow() { return *m_window; }
		void Close();
		ImGuiLayer* GetImGuiLayer() { return m_imguiLayer; }
		static Application& Get() { return *s_instance; }

	private:
		void Run();

		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imguiLayer;

		bool m_running = true;
		bool m_minimized = false;

		LayerStack m_layerStack;

		float m_lastFrameTime = 0.0f;

		static Application* s_instance;

		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}
