#pragma once

#include "Hazel/Core.h"

namespace Hazel {

	class HAZEL_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, unsigned int size);
	};

	class HAZEL_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount() const = 0;
		static IndexBuffer* Create(unsigned int* indices, unsigned int count);
	};
}