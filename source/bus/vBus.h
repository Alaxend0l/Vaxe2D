#pragma once

#include "types/vByte1.h"
#include "core/vMemory.h"

#include <cstdint>

namespace vaxe
{
    class vBus
    {
    public:
        vBus() {}
        ~vBus() {}


    public:
        void write(uint16_t address, byte_1 data)
        {
            ram[address] = data;
        }

        byte_1 read(uint16_t address, bool readOnly = false)
        {
            return ram[address];
        }

        vMemory ram{0xFF, MEMORY_ENDIAN_BIG};
        
    };
}