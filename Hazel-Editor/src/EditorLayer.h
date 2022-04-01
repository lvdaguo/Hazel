#pragma once

#include <Hazel.h>

namespace Hazel {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() { }

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		OrthographicCameraController m_cameraController;

		Ref<VertexArray> m_squareVA;
		Ref<Shader> m_flatColorShader;
		Ref<Framebuffer> m_framebuffer;

		Ref<Texture2D> m_checkerboardTexture;

		glm::vec4 m_squareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};


}