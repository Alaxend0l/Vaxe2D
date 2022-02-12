#pragma once

#include "types/vByte4.h"

#include "core/vWindow.h"
#include "core/vFramebuffer.h"

#include "entity/vScene.h"
#include "entity/vEntity.h"
#include "entity/vComponent.h"

namespace vaxe
{
    class vRenderer
    {
    public:
        vRenderer(SDL_Window* window, byte_4 flags);
        ~vRenderer();

        void PerformRender(SDL_Texture* texture);
        int PerformSceneRender(std::shared_ptr<vScene> scene, vFramebuffer* buffer);

        SDL_Renderer* GetRenderer() { return m_renderer; }
    private:
        SDL_Renderer* m_renderer;
        SDL_Window* m_window;
        byte_4 m_flags;
    };
}