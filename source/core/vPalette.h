#pragma once

#include "types/vByte1.h"
#include "types/vByte8.h"

#include <vector>
#include <iostream>

namespace vaxe
{
    struct vColor
    {
        byte_1 r, g, b, a;
    };

    class vPalette
    {
    public:
        vPalette() {}
        ~vPalette() {}

        void ClearPalette() {m_colors.clear();}
        void AddColor(vColor color) {m_colors.push_back(color);}
        void AddColor(byte_1 red, byte_1 green, byte_1 blue, byte_1 alpha) {m_colors.push_back(vColor{red, green, blue, alpha});}

        vColor& operator[](byte_8 offset)
        {
            if (offset >= m_colors.size())
            {
                std::cout << "Out of bounds exception: vPalette" << std::endl;
                exit(0);
            }
            return m_colors[offset];
        }
    private:
        std::vector<vColor> m_colors;
    };
}