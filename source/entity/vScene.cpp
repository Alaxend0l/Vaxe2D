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

        entity.AddComponent<Transform2D>();
        entity.AddComponent<EntityInfo>(true, name.empty() ? "New Entity" : name);

        return entity;
    }

    void vScene::DestroyEntity(vEntity entity)
    {
        registry.destroy(entity);
    }
}