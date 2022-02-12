#pragma once

#include "core/vWindow.h"

namespace vaxe
{
    class vTexture
    {
    public:
        vTexture(SDL_Renderer* renderer, std::string path);
        ~vTexture();

        SDL_Texture* GetTexture() { return m_texture; }
        int GetTextureWidth() { return m_width; }
        int GetTextureHeight() { return m_height; }
        
    private:
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
        int m_width;
        int m_height;
    };
}