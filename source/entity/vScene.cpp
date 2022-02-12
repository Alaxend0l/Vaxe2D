#include "entity/vScene.h"
#include "entity/vEntity.h"
#include "entity/vComponent.h"

namespace vaxe
{
    vScene::vScene() { }
    vScene::~vScene() { }

    vEntity vScene::CreateEntity(const std::string& name)
    {
        vEntity entity = {registry.create(), this};

        auto& info = entity.AddComponent<EntityInfo>();
        info.name = name;
        entity.AddComponent<Transform2D>();

        return entity;
    }

    void vScene::DestroyEntity(vEntity entity)
    {
        registry.destroy(entity);
    }
}