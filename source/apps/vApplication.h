#pragma once

#include <cstddef>

namespace vaxe
{
    class vApplication
    {
    public:
        virtual int Run() {return -1;}

        unsigned char* rom;
        size_t romSize;

    protected:
        bool quit{false};
    };
}