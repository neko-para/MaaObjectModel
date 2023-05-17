#pragma once

#include "port.h"
#include "type.h"

extern "C"
{
    MResult MAA_API MaaRtAlloc(MUInt size, MHandle* out);
    MResult MAA_API MaaRtFree(MHandle handle);
}
