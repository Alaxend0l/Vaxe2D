#pragma once

#include "apps/vApplication.h"

#include "core/vWindow.h"
#include "core/vRenderer.h"
#include "core/vMemory.h"
#include "core/vFramebuffer.h"
#include "core/vPalette.h"

namespace vaxe
{
    class vApp_Chip8 : vApplication
    {
    public:
        int Run() override;

        unsigned char* rom;
        size_t romSize;

    private:
        void InitializeValues();
        void DrawSprite(vFramebuffer* framebuffer, unsigned short x, unsigned short y, unsigned short height);

        vMemory memory { 4096 , MEMORY_ENDIAN_BIG };
        vPalette palette {};

        // Small Values

        unsigned short opcode = 0x0;
        unsigned short indexRegister = 0x0;
        unsigned short programCounter = 0x200;
        unsigned short stackPointer = 0x0;

        unsigned char delayTimer = 0x0;
        unsigned char soundTimer = 0x0;

        unsigned short stack[16];
        unsigned char key[16];
        unsigned char v[16];

        unsigned char fonts[80]
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

        unsigned char x = 0x0;
        unsigned char y = 0x0;
        unsigned char n = 0x0;
        unsigned char nn = 0x0;
        unsigned short nnn = 0x0;
    };
}