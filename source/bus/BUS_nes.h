#pragma once

#include "bus/vBus.h"

#include "cpu/CPU_olc6502.h"

namespace vaxe
{
    class vBUS_NES : vBus
    {
    public:
        vBUS_NES();
        ~vBUS_NES() {}

        vMemory ram{0xFFFF, MEMORY_ENDIAN_BIG};
        vCPU_olc6502 cpu{};

    };
}