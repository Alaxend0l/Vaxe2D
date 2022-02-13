#pragma once

// types

#include "types/vTexture.h"
#include "entity/imguiFuncs.h"

// std

#include <string>





namespace vaxe
{
    struct VaxeComponent : entt::type_list<>
    {
        bool componentEnabled = true;
        virtual int DrawComponent() {return -1;}
    };

    struct EntityInfo : VaxeComponent
    {
        bool isEnabled = true;
        std::string name = "UNNAMED";

        int DrawComponent() override
        {
            ImGui::BeginChild("EntityInfo", ImVec2(0, 36), true);
            ImGui::Checkbox("##EnabledCheckbox", &isEnabled);
            ImGui::SameLine();
            ImGui::InputText("##Name", &name);

            ImGui::EndChild();
            return 0;
        }

    };

    struct Transform2D : VaxeComponent
    {
        glm::vec3 position = {0,0,0};
        glm::vec2 scale = {1,1};
        float rotation = 0;

        glm::mat2 mat2()
        {
            const float sin = glm::sin(rotation);
            const float cos = glm::cos(rotation);

            glm::mat2 rotMatrix{{cos,sin},{-sin,cos}};
            glm::mat2 scaleMatrix{{scale.x, 0},{0,scale.y}};

            return rotMatrix * scaleMatrix;
        }
        int DrawComponent() override
        {
            ImGui::BeginChild("Transform2D", ImVec2(0, 74), true);

            DrawVec3Control("Position", position);
            DrawVec1Control("Rotation", rotation);
            DrawVec2Control("Scale", scale, 1);

            ImGui::EndChild();
            return 0;
        }
    };



    struct SpriteRenderer : VaxeComponent
    {
        std::shared_ptr<vTexture> m_texture;
        glm::vec2 offset = {0,0};
        glm::vec2 tiling = {1,1};
        int DrawComponent() override
        {
            ImGui::BeginChild("Sprite Renderer", ImVec2(0, 74), true);
            DrawVec2Control("Offset", offset);
            DrawVec2Control("Tiling", tiling, 1);
            ImGui::EndChild();
            return 0;
        }
    };

    
}