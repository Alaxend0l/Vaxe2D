#include "cpu/CPU_olc6502.h"

namespace vaxe
{
    byte_1 vCPU_olc6502::read(uint16_t address)
    {
        return bus->read(address, false);
    }

    void vCPU_olc6502::write(uint16_t address, byte_1 data)
    {
        bus->write(address, data);
    }
}