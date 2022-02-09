#pragma once

#include "apps/vApplication.h"

#include "bus/BUS_nes.h"

#include "cpu/CPU_olc6502.h"

#include "core/vWindow.h"
#include "core/vRenderer.h"
#include "core/vMemory.h"
#include "core/vFramebuffer.h"
#include "core/vPalette.h"

namespace vaxe
{
    class vApp_NES : vApplication
    {
    public:
        int Run() override;

        byte_1* rom;
        size_t romSize;

    private:
        void InitializeValues();
        void PrintDebugData();

        vBUS_NES bus {};

        vPalette palette {};

        /// Small Values

        uint64_t cycle = 0;

        // Program Counter
        uint16_t pc = 0x0;

        // Stack Pointer
        uint8_t sp = 0x0;

        //General Purpose Registers
        byte_1 gpr_a = 0x00;
        byte_1 gpr_x = 0x00;
        byte_1 gpr_y = 0x00;

        /// Temporary Values! Not normally part of the NES
        byte_1 instruction = 0x00;
    };
}