#pragma once

#include "types/vByte1.h"

#include <stdint.h>
#include <iostream>

#define MEMORY_ENDIAN_BIG (uint8_t)0
#define MEMORY_ENDIAN_LITTLE (uint8_t)1


namespace vaxe
{
    class vMemory
    {
    public:
        vMemory(uint64_t size, uint8_t endian);
        ~vMemory();

        void ClearMemory();

        void InsertRom(byte_1* rom, size_t romSize, uint64_t offset);

        //bool WriteData(uint64_t offset, T data);
        //T ReadData(uint64_t offset);
        byte_1& operator[](uint64_t);

    private:

        byte_1* m_data;
        uint8_t m_endian;
        uint64_t m_size;
    };
}