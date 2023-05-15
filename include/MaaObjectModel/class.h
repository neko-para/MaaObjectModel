#pragma once

#include "object.h"
#include "port.h"
#include "type.h"

extern "C"
{
    MResult MAA_API MaaRtInitClass();
    MResult MAA_API MaaRtRegisterClass(const MUUID* cid, MFactory factory);
    MResult MAA_API MaaRtLocateClass(const MUUID* cid, MFactory* factory);
}
