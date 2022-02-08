#include "core/vFramebuffer.h"

namespace vaxe
{
    vFramebuffer::vFramebuffer(SDL_Renderer* renderer, uint32_t width, uint32_t height) : m_renderer(renderer), m_width(width), m_height(height)
    {
        m_size = width * height * 3;
        m_data = new unsigned char[m_size]();

        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

        ClearBuffer();
    }

    vFramebuffer::~vFramebuffer()
    {
        free(m_data);
    }

    void vFramebuffer::ClearBuffer()
    {
        memset(GetDataStart(), 0x00, m_size);
    }

    void vFramebuffer::UpdateTexture()
    {
        SDL_UpdateTexture(m_texture, NULL, GetDataStart(), m_size/m_height);
    }
}