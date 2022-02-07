#pragma once

#include <stdint.h>

#define MEMORY_ENDIAN_BIG (uint8_t)0
#define MEMORY_ENDIAN_LITTLE (uint8_t)1


namespace vaxe
{
    class vMemory
    {
    public:
        vMemory(uint64_t size, uint8_t endian);
        ~vMemory();

        //bool WriteData(uint64_t offset, T data);
        //T ReadData(uint64_t offset);

    private:
        bool writeByte(uint64_t offset, unsigned char byte);
        unsigned char readByte(uint64_t offset) { return m_data[offset]; }

        unsigned char* m_data;
        uint8_t m_endian;
        uint64_t m_size;
    };
}