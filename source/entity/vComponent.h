#pragma once

// types

#include "types/vByte4.h"
#include "types/vTexture.h"
#include "entity/imguiFuncs.h"

// std

#include <string>
#include <memory>
#include <vector>


namespace vaxe
{
    class VaxeComponent
    {
    public:
        VaxeComponent() {}
        bool componentEnabled = true;
        const byte_4 componentIndex = 0;
        virtual int DrawComponent() {return -1;}
    };

    class EntityInfo : public VaxeComponent
    {
    public:
        EntityInfo () {}
        const byte_4 componentIndex = 1;

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

    class Transform2D : public VaxeComponent
    {
    public:
        Transform2D(){}
        const byte_4 componentIndex = 2;

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



    class SpriteRenderer : public VaxeComponent
    {
    public:
        SpriteRenderer(){}
        const byte_4 componentIndex = 3;

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