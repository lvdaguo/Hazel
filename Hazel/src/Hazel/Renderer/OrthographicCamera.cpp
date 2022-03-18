#include "hzpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	{
		m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_viewMatrix = glm::mat4(1.0f); // rotation = 0, position = 0 0 0
		m_viewProjectMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0, 0, 1));
		transform = glm::translate(transform, m_position);

		m_viewMatrix = glm::inverse(transform);
		m_viewProjectMatrix = m_projectionMatrix * m_viewMatrix;
	}
}