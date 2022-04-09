#pragma once

#include <entt.hpp>

#include "Hazel/Core/Timestep.h"

namespace Hazel {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void OnUpdate(Timestep ts);
		void OnViewportResize(unsigned int width, unsigned int height);

	private:
		entt::registry m_registry;
		unsigned int m_viewportWidth = 0, m_viewportHeight = 0;

		friend class Entity;
	};

}