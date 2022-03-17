#pragma once

#include "Hazel/Core.h"

namespace Hazel {
	class HAZEL_API Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		unsigned int m_rendererID;
	};

}