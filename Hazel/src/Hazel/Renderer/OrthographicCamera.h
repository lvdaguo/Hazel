#pragma once

#include <Hazel/Core/Core.h>
#include <glm/glm.hpp>

namespace Hazel {

	class HAZEL_API OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		inline const glm::vec3& GetPosition() const { return m_position; }
		inline void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }

		inline float GetRotation() const { return m_rotation; }
		inline void SetRotation(float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }
		
		inline const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjectMatrix; }

	private:
		void RecalculateViewMatrix();

		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjectMatrix;

		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		float m_rotation = 0.0f;
 	};

}