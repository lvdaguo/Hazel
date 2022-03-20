#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {

	class HAZEL_API Texture
	{
	public:
		virtual ~Texture() { }

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void Bind(unsigned int slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}