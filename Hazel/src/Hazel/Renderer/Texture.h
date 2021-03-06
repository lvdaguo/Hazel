#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {

	class Texture
	{
	public:
		virtual ~Texture() { }

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual unsigned int GetRendererID() const = 0;

		virtual void SetData(void* data, unsigned int size) = 0;

		virtual void Bind(unsigned int slot = 0) const = 0;

		virtual bool operator == (const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(unsigned int width, unsigned int height);
		static Ref<Texture2D> Create(const std::string& path);
	};
}