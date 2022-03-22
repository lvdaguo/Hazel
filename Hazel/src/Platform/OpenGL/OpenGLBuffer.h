#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int size);
		OpenGLVertexBuffer(float* vertices, unsigned int size);

		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, unsigned int size) override;

		virtual const BufferLayout& GetLayout() const override { return m_layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }

	private:
		unsigned int m_rendererID;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	
		inline virtual unsigned int GetCount() const override { return m_count; }

	private:
		unsigned int m_rendererID;
		unsigned int m_count;
	};
}