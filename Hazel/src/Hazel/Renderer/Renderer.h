#pragma once

#include "Hazel/Core/Core.h"
#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace Hazel {
	class HAZEL_API Renderer
	{
	public:
		static void Init();
		static void OnWindowReisze(unsigned int width, unsigned int height);
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_sceneData;
	};
}