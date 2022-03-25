#pragma once

#include "RendererAPI.h"

namespace Hazel {

	class RenderCommand
	{
	public:
		static void Init()
		{
			s_rendererAPI->Init();
		}

		static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
		{
			s_rendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_rendererAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_rendererAPI->Clear();
		}

		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, unsigned int count = 0)
		{
			s_rendererAPI->DrawIndexed(vertexArray, count);
		}
		
	private:
		static Scope<RendererAPI> s_rendererAPI;
	};

}