#pragma once

#include "Hazel/Renderer/Framebuffer.h"

namespace Hazel {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(unsigned int width, unsigned int height) override;

		virtual unsigned int GetColorAttachmentRendererID() const override { return m_colorAttachment; }
		virtual const FramebufferSpecification& GetSpecification() const override { return m_specification; }

	private:
		unsigned int m_rendererID = 0;
		unsigned int m_colorAttachment = 0, m_depthAttachment = 0;
		FramebufferSpecification m_specification;
	};
}