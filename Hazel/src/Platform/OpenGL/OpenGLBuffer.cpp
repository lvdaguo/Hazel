#include "hzpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Hazel {
	/////////////////////////////////////////////////////////////////////////////
	// VertexBuffer /////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int size)
	{
		HZ_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size)
	{
		HZ_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_rendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		HZ_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		HZ_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void OpenGLVertexBuffer::SetData(const void* data, unsigned int size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	/////////////////////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count)
		: m_count(count)
	{
		HZ_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_rendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		HZ_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		HZ_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}