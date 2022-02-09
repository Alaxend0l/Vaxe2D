#pragma once

#include "types/vByte1.h"
#include "types/vByte2.h"

#include <cstdint>

namespace vaxe
{
    class vCPU
    {
    public:
        vCPU(){}
        ~vCPU(){}

        void write(byte_2 address, byte_1 data){}

        byte_1 read(byte_2 address){return 0x00;}
    };
}