#pragma once

typedef unsigned int byte_4;

namespace vByte4
{
    static void SetXToY(byte_4& a, byte_4& b) {a=b;}
    static void SetXToEitherXOrY(byte_4& a, byte_4& b) {a|=b;}

}