#pragma once

#include "apps/vApplication.h"

namespace vaxe
{
    class vApp_Chip8 : vApplication
    {
    public:
        int Run() override;
    };
}