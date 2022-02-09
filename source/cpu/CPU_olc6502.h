#pragma once

#include "cpu/vCPU.h"

#include "bus/vBus.h"

namespace vaxe
{
    class vCPU_olc6502 : vCPU
    {
    public:
        vCPU_olc6502() {}
        ~vCPU_olc6502() {}

    public:
        // CPU Core registers, exposed as public here for ease of access from external
        // examinors. This is all the 6502 has.
        byte_1     a      = 0x00;		// Accumulator Register
        byte_1     x      = 0x00;		// X Register
        byte_1     y      = 0x00;		// Y Register
        byte_1     stkp   = 0x00;		// Stack Pointer (points to location on bus)
        uint16_t pc     = 0x0000;	// Program Counter
        byte_1     status = 0x00;		// Status Register

        void ConnectBus(vBus *n) { bus = n; }

        enum FLAGS6502
        {
            C = (1 << 0),	// Carry Bit
            Z = (1 << 1),	// Zero
            I = (1 << 2),	// Disable Interrupts
            D = (1 << 3),	// Decimal Mode (unused in this implementation)
            B = (1 << 4),	// Break
            U = (1 << 5),	// Unused
            V = (1 << 6),	// Overflow
            N = (1 << 7),	// Negative
        };

    private:
        // Convenience functions to access status register
	    byte_1 GetFlag(FLAGS6502 f);
	    void SetFlag(FLAGS6502 f, bool v);

        vBus* bus = nullptr;
        byte_1 read  (uint16_t address);
        void write (uint16_t address, byte_1 data);
        
    };
}