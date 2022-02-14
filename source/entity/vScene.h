#pragma once

#include <memory>
#include <vector>

namespace vaxe
{
    class vEntity;
    
    class vScene
    {
    public:
        vScene();
        ~vScene();

        std::shared_ptr<vEntity> CreateEntity(const std::string& name);
        void DestroyEntity(std::shared_ptr<vEntity> entity);

        int GetEntityCount() { return m_entities.size(); }
        std::shared_ptr<vEntity> GetEntity(int index) { return m_entities.at(index); }

    private:
        std::vector<std::shared_ptr<vEntity>> m_entities;

        unsigned int m_pid;

        friend class vEntity;
        friend class vLayer_Hierarchy;

    };
}