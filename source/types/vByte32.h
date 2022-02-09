#pragma once

struct byte_32
{
    int bytes[32];
};

namespace vByte32
{
    static void SetXToY(byte_32& a, byte_32& b) {a=b;}
    //static void SetXToEitherXOrY(byte_32& a, byte_32& b) {a|=b;}

}