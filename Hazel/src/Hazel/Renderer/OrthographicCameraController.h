#pragma once

#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Core/Timestep.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = true);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_camera; }
		const OrthographicCamera& GetCamera() const { return m_camera; }

		float GetZoomLevel() const { return m_zoomLevel; }
		void SetZoomLevel(float level) { m_zoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		float m_aspectRatio;
		float m_zoomLevel = 1.0f;
		OrthographicCamera m_camera;

		bool m_rotation;

		glm::vec3 m_cameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_cameraRotation = 0.0f; // In degrees, in the anti-clockwise direction
		float m_cameraTranslationSpeed = 5.0f, m_cameraRotationSpeed = 180.0f;
	};

}