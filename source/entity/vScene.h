#pragma once

#include <entt.hpp>

namespace vaxe
{
    class vEntity;
    
    class vScene
    {
    public:
        vScene();
        ~vScene();

        vEntity CreateEntity(const std::string& name);
        void DestroyEntity(vEntity entity);

        entt::registry& GetRegistry() { return registry; }

    private:
        entt::registry registry;
        
        vEntity* selectedEntity;

        friend class vEntity;
    };
}