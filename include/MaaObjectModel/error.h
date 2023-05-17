#pragma once

#include "port.h"
#include "type.h"

extern "C"
{
    void MAA_API MaaRtSetLastError(MRString err);
    MString MAA_API MaaRtGetLastError();
}
