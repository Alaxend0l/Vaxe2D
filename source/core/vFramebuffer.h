#pragma once

// types

#include "types/vByte1.h"

// core

#include "core/vWindow.h"
#include "core/vPalette.h"

// std

#include <stdint.h>
#include <vector>

namespace vaxe
{
    class vFramebuffer
    {
    public:
        vFramebuffer(SDL_Renderer* renderer, uint32_t width, uint32_t height);
        ~vFramebuffer();

        void ClearBuffer();
        void UpdateTexture();

        void SetColor(uint32_t x, uint32_t y, vColor color);
        void SetColor(uint64_t offset, vColor color);

        vColor GetColor(uint64_t offset);

        byte_1* GetDataStart() { return &m_data[0]; }
        uint64_t GetDataSize() { return m_size; }
        SDL_Texture* GetTexture() { return m_texture; }

    private:
        byte_1* m_data;

        uint32_t m_width;
        uint32_t m_height;
        uint64_t m_size;

        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
    };
}