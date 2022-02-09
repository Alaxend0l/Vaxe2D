#include "core/vFramebuffer.h"

namespace vaxe
{
    vFramebuffer::vFramebuffer(SDL_Renderer* renderer, uint32_t width, uint32_t height) : m_renderer(renderer), m_width(width), m_height(height)
    {
        m_size = width * height * 4;
        m_data = new byte_1[m_size]();

        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

        ClearBuffer();
    }

    vFramebuffer::~vFramebuffer()
    {
        free(m_data);
    }

    void vFramebuffer::SetColor(uint32_t x, uint32_t y, vColor color)
    {
        uint64_t offset = (m_width * y + x);
        SetColor(offset, color);
    }

    void vFramebuffer::SetColor(uint64_t offset, vColor color)
    {
        uint64_t trueOffset = offset * 4;
        m_data[trueOffset + 0] = color.r;
        m_data[trueOffset + 1] = color.g;
        m_data[trueOffset + 2] = color.b;
        m_data[trueOffset + 3] = color.a;
    }

    vColor vFramebuffer::GetColor(uint64_t offset)
    {
        uint64_t trueOffset = offset * 4;
        
        return {m_data[trueOffset + 0],
        m_data[trueOffset + 1],
        m_data[trueOffset + 2],
        m_data[trueOffset + 3]};
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