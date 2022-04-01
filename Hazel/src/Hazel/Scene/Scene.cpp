#include "hzpch.h"
#include "Scene.h"

#include "Components.h"
#include "Hazel/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Hazel {

	static void DoMath(const glm::mat4& transform)
	{

	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{

	}

	Scene::Scene()
	{
#if ENTT_EXAMPLE_CORE
		entt::entity entity = m_registry.create();
		m_registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		m_registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();
	
		if (m_registry.has<TransformComponent>(entity))
			TransformComponent& transform = m_registry.get<TransformComponent>(entity);

		auto view = m_registry.view<TransformComponent>();
		for (auto entity : view)
		{
			TransformCompoenent& transform = view.get<TransformCompoenent>(entity);
		}

		auto group = m_registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, MeshCompoenent>(entity);
		}
#endif
	}

	Scene::~Scene()
	{

	}

	entt::entity Scene::CreateEntity()
	{
		return m_registry.create();
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}