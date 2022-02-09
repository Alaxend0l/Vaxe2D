#pragma once

typedef unsigned char byte_1;

namespace vByte1
{
    static void SetXToY(byte_1& a, byte_1& b) {a=b;}
    static void SetXToEitherXOrY(byte_1& a, byte_1& b) {a|=b;}

}