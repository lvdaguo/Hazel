#include "hzpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		// TODO: texid
	};

	struct Renderer2DData
	{
		const unsigned int MaxQuads = 10000;
		const unsigned int MaxVertices = MaxQuads * 4;
		const unsigned int MaxIndices = MaxQuads * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		unsigned int QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};

	static Renderer2DData s_data;

	void Renderer2D::Init()
	{
		HZ_PROFILE_FUNCTION();

		s_data.QuadVertexArray = VertexArray::Create();
	
		s_data.QuadVertexBuffer = VertexBuffer::Create(s_data.MaxVertices * sizeof(QuadVertex));
		s_data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"}
		});

		s_data.QuadVertexArray->AddVertexBuffer(s_data.QuadVertexBuffer);

		s_data.QuadVertexBufferBase = new QuadVertex[s_data.MaxVertices];

		unsigned int* quadIndices = new unsigned int[s_data.MaxIndices];

		unsigned int offset = 0;
		for (unsigned int i = 0; i < s_data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_data.MaxIndices);
		s_data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_data.WhiteTexture = Texture2D::Create(1, 1);
		unsigned int whiteTextureData = 0xffffffff;
		s_data.WhiteTexture->SetData(&whiteTextureData, sizeof(unsigned int));

		s_data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_data.TextureShader->Bind();
		s_data.TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		HZ_PROFILE_FUNCTION();

	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		HZ_PROFILE_FUNCTION();

		s_data.TextureShader->Bind();
		s_data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_data.QuadIndexCount = 0;
		s_data.QuadVertexBufferPtr = s_data.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		HZ_PROFILE_FUNCTION();

		unsigned int dataSize = (uint8_t*)s_data.QuadVertexBufferPtr - (uint8_t*)s_data.QuadVertexBufferBase;
		s_data.QuadVertexBuffer->SetData(s_data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(s_data.QuadVertexArray, s_data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		HZ_PROFILE_FUNCTION();

		s_data.QuadVertexBufferPtr->Position = position;
		s_data.QuadVertexBufferPtr->Color = color;
		s_data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_data.QuadVertexBufferPtr++;

		s_data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		s_data.QuadVertexBufferPtr->Color = color;
		s_data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_data.QuadVertexBufferPtr++;

		s_data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		s_data.QuadVertexBufferPtr->Color = color;
		s_data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_data.QuadVertexBufferPtr++;

		s_data.QuadVertexBufferPtr->Position = { position.x , position.y + size.y, 0.0f };
		s_data.QuadVertexBufferPtr->Color = color;
		s_data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_data.QuadVertexBufferPtr++;

		s_data.QuadIndexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		HZ_PROFILE_FUNCTION();

		s_data.TextureShader->SetFloat4("u_Color", tintColor);
		s_data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data.TextureShader->SetMat4("u_Transform", transform);

		s_data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_data.QuadVertexArray);
	}


	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		HZ_PROFILE_FUNCTION();

		s_data.TextureShader->SetFloat4("u_Color", color);
		s_data.TextureShader->SetFloat("u_tilingFactor", 1.0f);
		s_data.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data.TextureShader->SetMat4("u_Transform", transform);
		s_data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_data.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad( { position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		HZ_PROFILE_FUNCTION();

		s_data.TextureShader->SetFloat4("u_Color", tintColor);
		s_data.TextureShader->SetFloat("u_tilingFactior", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data.TextureShader->SetMat4("u_Transform", transform);
		s_data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_data.QuadVertexArray);
	}
}