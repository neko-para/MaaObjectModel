#pragma once

#include "port.h"
#include "type.h"

extern "C"
{
    MResult MAA_API MaaRtSetLastError(MRString err);
    MResult MAA_API MaaRtGetLastError(MString* err);
}
