#pragma once

typedef unsigned short byte_2;

namespace vByte2
{
    static void SetXToY(byte_2& a, byte_2& b) {a=b;}
    static void SetXToEitherXOrY(byte_2& a, byte_2& b) {a|=b;}

}