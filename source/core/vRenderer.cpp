#include "core/vRenderer.h"

namespace vaxe
{
    vRenderer::vRenderer(SDL_Window* window, byte_4 flags) : m_window(window), m_flags(flags)
    {
        m_renderer = SDL_CreateRenderer(m_window, -1, m_flags);
    }

    vRenderer::~vRenderer()
    {
        SDL_DestroyRenderer(m_renderer);
    }

    void vRenderer::PerformRender(SDL_Texture* texture)
    {
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
    }
}