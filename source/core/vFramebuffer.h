#pragma once

#include "core/vWindow.h"

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

        void TESTONLY_SetValue(uint64_t offset, const char value) {if (offset < m_size) m_data[offset] = value;}

        unsigned char* GetDataStart() { return m_data; }
        uint64_t GetDataSize() { return m_size; }
        SDL_Texture* GetTexture() { return m_texture; }

    private:
        unsigned char* m_data;

        uint32_t m_width;
        uint32_t m_height;
        uint64_t m_size;

        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
    };
}