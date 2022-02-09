#pragma once

#include "apps/vApplication.h"

namespace vaxe
{
    class vApp_First : vApplication
    {
    public:
        int Run() override;

        unsigned char* rom;
        size_t romSize;
    };
}