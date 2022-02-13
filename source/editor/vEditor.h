#pragma once

// layers

#include "layers/layer_dock.h"
#include "layers/layer_hierarchy.h"
#include "layers/layer_properties.h"
#include "layers/layer_filesystem.h"

// types

#include "types/vByte1.h"
#include "types/vTexture.h"

// filesystem

#include "filesystem/vProject.h"

// core

#include "core/vWindow.h"
#include "core/vRenderer.h"
#include "core/vFramebuffer.h"

// entity

#include "entity/vScene.h"

// std

#include <vector>

namespace vaxe
{
    class vEditor
    {
    public:
        vEditor();
        ~vEditor();

        int Run();
    
    private:

        vWindow m_window {1280, 720, "Vaxe2D"};
        vRenderer m_renderer {m_window.GetWindow(), SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED };

        std::shared_ptr<vProject> m_project;
        

        // Framebuffers

        vFramebuffer m_editorBuffer {m_renderer.GetRenderer(), 100, 100};
        vFramebuffer m_gameBuffer {m_renderer.GetRenderer(), 100, 100};

        std::vector<std::shared_ptr<vLayer>> m_editorLayers;

        byte_1* m_projectFile;

        bool exit = false;
        
    };
}