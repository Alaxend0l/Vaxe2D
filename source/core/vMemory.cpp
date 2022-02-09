#include "core/vMemory.h"

#include <cstring>

namespace vaxe
{
    vMemory::vMemory(uint64_t size, uint8_t endian) : m_size(size), m_endian(endian)
    {
        m_data = new byte_1[size];
    }

    vMemory::~vMemory()
    {
        //free(m_data);
    }

    void vMemory::ClearMemory()
    {
        memset(m_data, 0x00, m_size);
    }

    void vMemory::InsertRom(byte_1* rom, size_t romSize, uint64_t offset)
    {
        for (int i = 0; i < romSize; ++i)
        {
            m_data[i+offset] = rom[i];
        }
    }

    byte_1& vMemory::operator[](uint64_t offset)
    {
        if (offset < 0 || offset >= m_size)
        {
            std::cout << "Out of bounds exception: vMemory" << std::endl;
            exit(0);
        }
        return m_data[offset];
    }
}