#include "types/vTexture.h"

namespace vaxe
{
    vTexture::vTexture(SDL_Renderer* renderer, std::string path) : m_renderer(renderer)
    {
        IMG_Init(IMG_INIT_PNG);
        m_texture = IMG_LoadTexture(m_renderer, path.c_str());
        SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);
    }

    vTexture::~vTexture()
    {
        SDL_DestroyTexture(m_texture);
    }
}