#include "core/vMemory.h"

namespace vaxe
{
    vMemory::vMemory(uint64_t size, uint8_t endian) : m_size(size), m_endian(endian)
    {
        m_data = new unsigned char(size);
    }

    vMemory::~vMemory()
    {

    }

    bool vMemory::writeByte(uint64_t offset, unsigned char byte)
    {
        m_data[offset] = byte;
        return true;
    }
}