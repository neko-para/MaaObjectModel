#pragma once

#include <cstdint>

using MInt = int64_t;
using MUInt = uint64_t;
using MFloat = double;
using MBool = uint8_t;
using MChar = char;
using MRString = const MChar*;

using MHandle = void*;
using MString = MHandle;

struct MUUID
{
    char id[37];
};
