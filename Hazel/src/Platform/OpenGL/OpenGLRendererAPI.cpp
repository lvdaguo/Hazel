#include "hzpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Hazel {

	void OpenGLMessageCallback(
		unsigned int source,
		unsigned int type,
		unsigned int id,
		unsigned int severity,
		int length,
		const char* message,
		const void* userParam
	)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:			HZ_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:			HZ_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:				HZ_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION:	HZ_CORE_TRACE(message); return;
		}
		HZ_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init()
	{
		HZ_PROFILE_FUNCTION();

#ifdef HZ_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, unsigned int indexCount)
	{
		unsigned int count = indexCount == 0 ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}