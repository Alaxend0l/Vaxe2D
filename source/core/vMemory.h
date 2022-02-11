#pragma once

#include "types/vByte1.h"
#include "types/vByte8.h"

#include <stdint.h>
#include <iostream>

#define MEMORY_ENDIAN_BIG (byte_1)0
#define MEMORY_ENDIAN_LITTLE (byte_1)1


namespace vaxe
{
    class vMemory
    {
    public:
        vMemory(byte_8 size, byte_1 endian);
        ~vMemory();

        void ClearMemory();

        void InsertRom(byte_1* rom, size_t romSize, byte_8 offset);

        //bool WriteData(uint64_t offset, T data);
        //T ReadData(uint64_t offset);
        byte_1& operator[](byte_8);

    private:

        byte_1* m_data;
        byte_1 m_endian;
        byte_8 m_size;
    };
}