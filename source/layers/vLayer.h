#pragma once

#include "entity/imguiFuncs.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cstddef>
#include <string>

namespace vaxe
{
    class vLayer
    {
    public:
        virtual int OnCreate() {return -1;}
        virtual int OnUpdate() {return -1;}
        virtual int OnDraw() {return -1;}
        virtual int OnDestroy() {return -1;}

    protected:
        ImGuiDockNodeFlags m_dockNodeFlags;
        ImGuiWindowFlags m_windowFlags;
        bool m_open {true};

    };
}