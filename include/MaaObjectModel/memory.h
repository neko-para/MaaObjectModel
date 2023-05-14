#pragma once

#include "port.h"
#include "type.h"

extern "C"
{
    MHandle MAA_API MaaRtAlloc(MUInt size);
    void MAA_API MaaRtFree(MHandle handle);
}
