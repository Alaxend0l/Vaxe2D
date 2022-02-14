#include "entity/vScene.h"
#include "entity/vEntity.h"
#include "entity/vComponent.h"

namespace vaxe
{
    vScene::vScene() { }
    vScene::~vScene() { }

    std::shared_ptr<vEntity> vScene::CreateEntity(const std::string& name)
    {
        std::shared_ptr<vEntity> entity = std::make_shared<vEntity>(this, m_pid);

        entity->SetName(name);

        auto info = entity->AddComponent<EntityInfo>();
        info->name = name;
        
        entity->AddComponent<Transform2D>();

        m_pid++;

        m_entities.push_back(entity);

        return entity;
    }

    void vScene::DestroyEntity(std::shared_ptr<vEntity> entity)
    {
        //registry.destroy(entity);
    }
}