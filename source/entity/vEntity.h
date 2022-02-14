#pragma once

//core

#include "entity/vScene.h"
#include "entity/vComponent.h"

// std

#include <memory>
#include <vector>

namespace vaxe
{
    class vEntity
    {
    public:
        vEntity() = default;
		vEntity(vScene* _scene, unsigned int id);
		vEntity(const vEntity& other) = default;

		/*

		void AddComponent(std::shared_ptr<VaxeComponent> newComponent)
		{
			if (HasComponent(newComponent->componentIndex) == -1)
			{
				m_components.push_back(newComponent);
			}
		}

		*/

		template<typename T, typename... Args>
		std::shared_ptr<T> AddComponent(Args&&... args)
		{
			std::shared_ptr<T> newComponent = std::make_shared<T>(std::forward<Args>(args)...);
			if (HasComponent(newComponent->componentIndex) == -1)
			{
				m_components.push_back(newComponent);
			}
			return newComponent;
		}

		std::shared_ptr<VaxeComponent> GetComponent(int index)
		{
			return m_components.at(index);
		}
		
		int HasComponent(int componentType)
		{
			for (int i = 0; i < m_components.size(); i++)
			{
				if (m_components.at(i)->componentIndex == componentType)
				{
					return i;
				}
			}
			return -1;
		}

		void RemoveComponent()
		{

			//scene->registry.remove<T>(entityHandle);
		}

		void SetName(std::string newName) { m_name = newName; }
		

		std::string GetName() { return m_name; }
		bool GetEnabled() { return m_enabled; }
		unsigned int GetEntityID() { return m_entityID; }
		unsigned int GetComponentCount() { return m_components.size(); }

		unsigned int GetChildrenCount() { return m_childEntities.size(); }

    private:
		std::vector<std::shared_ptr<VaxeComponent>> m_components;
        std::vector<std::shared_ptr<vEntity>> m_childEntities;
		std::shared_ptr<vEntity> m_parent;

		std::string m_name;
		bool m_enabled = true;
		unsigned int m_entityID;
        vScene* scene = nullptr;
    };
}