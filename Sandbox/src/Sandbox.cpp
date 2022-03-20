#include <Hazel.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_cameraPosition(0.0f)
	{
		m_vertexArray.reset(Hazel::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

		Hazel::BufferLayout layout = {
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		m_vertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hazel::IndexBuffer::Create(indices, 3));

		m_vertexArray->SetIndexBuffer(indexBuffer);

		m_squareVA.reset(Hazel::VertexArray::Create());
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Hazel::Ref<Hazel::VertexBuffer> squareVB;
		squareVB.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Hazel::ShaderDataType::Float3, "a_Positon"},
			{ Hazel::ShaderDataType::Float2, "a_TexCoord"}
		});

		m_squareVA->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Hazel::Ref<Hazel::IndexBuffer> squareIB;
		squareIB.reset(Hazel::IndexBuffer::Create(squareIndices, 6));
		m_squareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;			

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout (location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;			

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		
		m_shader.reset(Hazel::Shader::Create(vertexSrc, fragmentSrc));
		
		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_flatColorShader.reset(Hazel::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));;
	
		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec2 v_TexCoord;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Hazel::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_transparent = Hazel::Texture2D::Create("assets/textures/window.png");

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Hazel::Timestep ts) override
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_cameraPosition.x -= m_cameraMoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_cameraPosition.x += m_cameraMoveSpeed * ts;

		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			m_cameraPosition.y += m_cameraMoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			m_cameraPosition.y -= m_cameraMoveSpeed * ts;

		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
			m_cameraRotation += m_cameraRotationSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
			m_cameraRotation -= m_cameraRotationSpeed * ts;

		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();

		m_camera.SetPosition(m_cameraPosition);
		m_camera.SetRotation(m_cameraRotation);

		Hazel::Renderer::BeginScene(m_camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_flatColorShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_Color", m_squareColor);

		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Hazel::Renderer::Submit(m_flatColorShader, m_squareVA, transform);
			}
		}

		//Hazel::Renderer::Submit(m_shader, m_vertexArray);

		m_texture->Bind(0);
		Hazel::Renderer::Submit(m_TextureShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_transparent->Bind(0);
		Hazel::Renderer::Submit(m_TextureShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Hazel::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_squareColor));
		ImGui::End();
	}
	
	void OnEvent(Hazel::Event& event) override
	{
	}

private:
	Hazel::Ref<Hazel::Shader> m_shader;
	Hazel::Ref<Hazel::VertexArray> m_vertexArray;

	Hazel::Ref<Hazel::Shader> m_flatColorShader, m_TextureShader;
	Hazel::Ref<Hazel::VertexArray> m_squareVA;

	Hazel::Ref<Hazel::Texture2D> m_texture, m_transparent;

	Hazel::OrthographicCamera m_camera;
	glm::vec3 m_cameraPosition; 

	float m_cameraMoveSpeed = 5.0f;
	float m_cameraRotation = 0.0f;
	float m_cameraRotationSpeed = 180.0f;

	glm::vec3 m_squareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() = default;
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}