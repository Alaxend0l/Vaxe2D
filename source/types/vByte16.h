#pragma once

typedef unsigned long long byte_16;

namespace vByte16
{
    static void SetXToY(byte_16& a, byte_16& b) {a=b;}
    static void SetXToEitherXOrY(byte_16& a, byte_16& b) {a|=b;}

}