#pragma once

//core

#include "entity/vScene.h"

//lib

#include <entt.hpp>

namespace vaxe
{
    class vEntity
    {
    public:
        vEntity() = default;
		vEntity(entt::entity handle, vScene* _scene);
		vEntity(const vEntity& other) = default;

        template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			T& component = scene->registry.emplace<T>(entityHandle, std::forward<Args>(args)...);
			//scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			return scene->registry.get<T>(entityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return scene->registry.try_get<T>(entityHandle) != NULL;
		}

		template<typename T>
		void RemoveComponent()
		{
			scene->registry.remove<T>(entityHandle);
		}

		template<typename T>
		auto GetAllComponents()
		{
			return scene->registry.try_get<T>(entityHandle);
		}

        operator bool() const { return entityHandle != entt::null; }
		operator entt::entity() const { return entityHandle; }
		operator uint32_t() const { return (uint32_t)entityHandle; }

		uint32_t GetEntityHandle() { return (uint32_t)entityHandle;}

		bool operator==(const vEntity& other) const
		{
			return entityHandle == other.entityHandle && scene == other.scene;
		}

		bool operator!=(const vEntity& other) const
		{
			return !(*this == other);
		}
    private:
        entt::entity entityHandle{entt::null};
        vScene* scene = nullptr;
    };
}