#pragma once

#include "core/vWindow.h"

namespace vaxe
{
    class vRenderer
    {
    public:
        vRenderer(SDL_Window* window, u_int32_t flags);
        ~vRenderer();

        void PerformRender(SDL_Texture* texture);

        SDL_Renderer* GetRenderer() { return m_renderer; }
    private:
        SDL_Renderer* m_renderer;
        SDL_Window* m_window;
        u_int32_t m_flags;
    };
}