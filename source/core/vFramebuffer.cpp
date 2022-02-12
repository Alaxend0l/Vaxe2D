#include "core/vFramebuffer.h"

namespace vaxe
{
    vFramebuffer::vFramebuffer(SDL_Renderer* renderer, byte_4 width, byte_4 height) : m_renderer(renderer), m_width(width), m_height(height)
    {
        m_size = width * height * 4;
        m_data = new byte_1[m_size]();

        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, m_width, m_height);

        ClearBuffer(0);
    }

    vFramebuffer::~vFramebuffer()
    {
        free(m_data);
    }

    void vFramebuffer::SetColor(byte_4 x, byte_4 y, vColor color)
    {
        byte_8 offset = (m_width * y + x);
        SetColor(offset, color);
    }

    void vFramebuffer::SetColor(byte_8 offset, vColor color)
    {
        byte_8 trueOffset = offset * 4;
        m_data[trueOffset + 0] = color.r;
        m_data[trueOffset + 1] = color.g;
        m_data[trueOffset + 2] = color.b;
        m_data[trueOffset + 3] = color.a;
    }

    vColor vFramebuffer::GetColor(byte_8 offset)
    {
        byte_8 trueOffset = offset * 4;
        
        return {m_data[trueOffset + 0],
        m_data[trueOffset + 1],
        m_data[trueOffset + 2],
        m_data[trueOffset + 3]};
    }

    void vFramebuffer::ClearBuffer(byte_1 value = 0xFF)
    {
        memset(GetDataStart(), value, m_size);
    }

    void vFramebuffer::UpdateTexture()
    {
        SDL_UpdateTexture(m_texture, NULL, GetDataStart(), m_size/m_height);
    }

    void vFramebuffer::ChangeTextureSize(byte_4 width, byte_4 height)
    {
        if (width != m_width || height != m_height)
        {
            m_width = width;
            m_height = height;
            m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
        }
    }
}