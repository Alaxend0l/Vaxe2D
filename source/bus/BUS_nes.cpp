#include "bus/BUS_nes.h"

namespace vaxe
{
    vBUS_NES::vBUS_NES()
    {
        cpu.ConnectBus(this);
    }
}