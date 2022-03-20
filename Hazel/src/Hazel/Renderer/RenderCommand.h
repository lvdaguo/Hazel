#pragma once

#include "RendererAPI.h"

namespace Hazel {

	class HAZEL_API RenderCommand
	{
	public:
		inline static void Init()
		{
			s_rendererAPI->Init();
		}

		inline static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
		{
			s_rendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_rendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_rendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_rendererAPI->DrawIndexed(vertexArray);
		}
		
	private:
		static RendererAPI* s_rendererAPI;
	};

}