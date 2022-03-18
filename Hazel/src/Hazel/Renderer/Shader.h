#pragma once

#include "Hazel/Core.h"
#include <glm/glm.hpp>

namespace Hazel {
	class HAZEL_API Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int m_rendererID;
	};

}