#include "core/vMemory.h"

#include <cstring>

namespace vaxe
{
    vMemory::vMemory(uint64_t size, uint8_t endian) : m_size(size), m_endian(endian)
    {
        m_data = new unsigned char(size);
    }

    vMemory::~vMemory()
    {

    }

    void vMemory::ClearMemory()
    {
        memset(m_data, 0x00, m_size);
    }

    void vMemory::InsertRom(unsigned char* rom, size_t romSize, uint64_t offset)
    {
        for (int i = 0; i < romSize; ++i)
        {
            m_data[i+offset] = rom[i];
        }
    }

    unsigned char& vMemory::operator[](uint64_t offset)
    {
        if (offset >= m_size)
        {
            std::cout << "Out of bounds exception: vMemory" << std::endl;
            exit(0);
        }
        return m_data[offset];
    }

    bool vMemory::writeByte(uint64_t offset, unsigned char byte)
    {
        m_data[offset] = byte;
        return true;
    }
}