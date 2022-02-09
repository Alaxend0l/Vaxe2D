#pragma once

#include "apps/vApplication.h"

namespace vaxe
{
    class vApp_First : vApplication
    {
    public:
        int Run() override;

        byte_1* rom;
        size_t romSize;
    };
}