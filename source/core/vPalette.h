#pragma once

#include <vector>
#include <iostream>

namespace vaxe
{
    struct vColor
    {
        unsigned char r, g, b, a;
    };

    class vPalette
    {
    public:
        vPalette() {}
        ~vPalette() {}

        void ClearPalette() {m_colors.clear();}
        void AddColor(vColor color) {m_colors.push_back(color);}

        vColor& operator[](uint64_t offset)
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