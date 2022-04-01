#pragma once

#include "Hazel/Renderer/Texture.h"

#include <glad/glad.h>

namespace Hazel {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(unsigned int width, unsigned int height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual unsigned int GetWidth() const override { return m_width; }
		virtual unsigned int GetHeight() const override { return m_height; }

		virtual unsigned int GetRendererID() const override { return m_rendererID; }

		virtual void SetData(void* data, unsigned int size) override;

		virtual void Bind(unsigned int slot = 0) const override;

		virtual bool operator == (const Texture& other) const override
		{
			return m_rendererID == ((OpenGLTexture2D&)other).m_rendererID;
		}

	private:
		std::stringbuf m_path;
		unsigned int m_width, m_height;
		unsigned int m_rendererID;
		GLenum m_internalFormat, m_dataFormat;
	};

}