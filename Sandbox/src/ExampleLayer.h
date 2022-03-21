#pragma once

#include <Hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer();

	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Hazel::Timestep ts) override; 

	void OnEvent(Hazel::Event& e) override;

private:
	Hazel::ShaderLibrary m_shaderLibrary;
	Hazel::Ref<Hazel::Shader> m_shader;
	Hazel::Ref<Hazel::VertexArray> m_vertexArray;

	Hazel::Ref<Hazel::Shader> m_flatColorShader;
	Hazel::Ref<Hazel::VertexArray> m_squareVA;

	Hazel::Ref<Hazel::Texture2D> m_texture, m_transparent;

	Hazel::OrthographicCameraController m_cameraController;

	glm::vec3 m_squareColor = { 0.2f, 0.3f, 0.8f };
};


