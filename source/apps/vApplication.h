#pragma once

#include "types/vByte1.h"

#include <cstddef>

namespace vaxe
{
    class vApplication
    {
    public:
        virtual int Run() {return -1;}

        byte_1* rom;
        size_t romSize;

    protected:
        bool quit{false};
    };
}