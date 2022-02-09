#pragma once

typedef unsigned long byte_8;

namespace vByte8
{
    static void SetXToY(byte_8& a, byte_8& b) {a=b;}
    static void SetXToEitherXOrY(byte_8& a, byte_8& b) {a|=b;}

}