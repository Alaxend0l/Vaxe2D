#pragma once

// types

#include "types/vTexture.h"

// std

#include <string>

// libs

#include <glm/gtc/matrix_transform.hpp>

namespace vaxe
{
    struct EntityInfo
    {
        bool isEnabled = true;
        std::string name = "UNNAMED";
    };

    struct Transform2D
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
    };

    struct SpriteRenderer
    {
        std::shared_ptr<vTexture> m_texture;
        glm::vec2 offset = {0,0};
        glm::vec2 tiling = {1,1};
    };
}