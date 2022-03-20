#include "hzpch.h"
#include "OrthographicCameraController.h"

#include "Hazel/Input.h"
#include "Hazel/KeyCodes.h"

namespace Hazel {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_aspectRatio(aspectRatio), m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel), m_rotation(rotation)
	{ }

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_cameraPosition.x -= m_cameraTranslationSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_cameraPosition.x += m_cameraTranslationSpeed * ts;

		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			m_cameraPosition.y += m_cameraTranslationSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			m_cameraPosition.y -= m_cameraTranslationSpeed * ts;

		if (m_rotation)
		{
			if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
				m_cameraRotation += m_cameraRotationSpeed * ts;
			else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
				m_cameraRotation -= m_cameraRotationSpeed * ts;
		}

		m_camera.SetPosition(m_cameraPosition);
		m_cameraTranslationSpeed = m_zoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_zoomLevel -= e.GetYOffset() * 0.25;
		m_zoomLevel = std::max(m_zoomLevel, 0.25f);
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}

}