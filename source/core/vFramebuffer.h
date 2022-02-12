#pragma once

// types

#include "types/vByte1.h"
#include "types/vByte4.h"
#include "types/vByte8.h"

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
        vFramebuffer(SDL_Renderer* renderer, byte_4 width, byte_4 height);
        ~vFramebuffer();

        void ClearBuffer(byte_1 value);
        void UpdateTexture();
        void ChangeTextureSize(byte_4 width, byte_4 height);

        void SetColor(byte_4 x, byte_4 y, vColor color);
        void SetColor(byte_8 offset, vColor color);

        vColor GetColor(byte_8 offset);

        byte_1* GetDataStart() { return &m_data[0]; }
        byte_8 GetDataSize() { return m_size; }
        SDL_Texture* GetTexture() { return m_texture; }

    private:
        byte_1* m_data;

        byte_4 m_width;
        byte_4 m_height;
        byte_8 m_size;

        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
    };
}