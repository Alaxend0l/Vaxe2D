#include "layers/layer_properties.h"



namespace vaxe
{
    template<typename T>
    void DrawIfComponentExists(vEntity* entity)
    {
        if (entity->HasComponent<T>())
        {
            ((VaxeComponent*)&entity->GetComponent<T>())->DrawComponent();
        }
    }
    int vLayer_Properties::OnCreate()
    {
        return -1;
    }

    int vLayer_Properties::OnUpdate()
    {
        return -1;
    }

    int vLayer_Properties::OnDraw()
    {
        ImGui::Begin("Properties");
        if (m_hierarchy->m_selectedEntity)
        {
            DrawIfComponentExists<EntityInfo>(&m_hierarchy->m_selectedEntity);
            DrawIfComponentExists<Transform2D>(&m_hierarchy->m_selectedEntity);
            DrawIfComponentExists<SpriteRenderer>(&m_hierarchy->m_selectedEntity);
        }

        ImGui::End();
        return -1;
    }

    int vLayer_Properties::OnDestroy()
    {
        return -1;
    }
}
