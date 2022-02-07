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
        vFramebuffer(uint32_t width, uint32_t height);

        void ClearBuffer();
        void Render(vWindow& window);

        unsigned char* GetDataStart() { return &m_data[0]; }

    private:
        std::vector <unsigned char> m_data;

        uint32_t m_width;
        uint32_t m_height;
    };
}