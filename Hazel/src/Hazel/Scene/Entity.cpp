#include "hzpch.h"
#include "Entity.h"

namespace Hazel {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_entityHandle(handle), m_scene(scene)
	{

	}

}