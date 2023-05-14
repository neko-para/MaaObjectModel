#pragma once

#include "port.h"
#include "type.h"

extern "C"
{
    MString MAA_API MaaRtCreateString(const MChar* str, MInt len);
    void MAA_API MaaRtDeleteString(MString str);
    MString MAA_API MaaRtDuplicateString(MString str);
    MRString MAA_API MaaRtGetStringData(MString str, MInt* len);
}
