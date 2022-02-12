#include "layers/layer_properties.h"

namespace vaxe
{
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
            if (m_hierarchy->m_selectedEntity.HasComponent<EntityInfo>())
            {
                EntityInfo& info = m_hierarchy->m_selectedEntity.GetComponent<EntityInfo>();

                ImGui::BeginChild("EntityInfo", ImVec2(0, 36), true);

                ImGui::Checkbox("##EnabledCheckbox", &info.isEnabled);
                ImGui::SameLine();
                ImGui::InputText("##Name", &info.name);

                ImGui::EndChild();
            }

            if (m_hierarchy->m_selectedEntity.HasComponent<Transform2D>())
            {
                Transform2D& component = m_hierarchy->m_selectedEntity.GetComponent<Transform2D>();

                ImGui::BeginChild("Transform2D", ImVec2(0, 74), true);

                DrawVec3Control("Position", component.position);
                DrawVec1Control("Rotation", component.rotation);
                DrawVec2Control("Scale", component.scale, 1);

                ImGui::EndChild();
            }
        }

        ImGui::End();
        return -1;
    }

    int vLayer_Properties::OnDestroy()
    {
        return -1;
    }
}
