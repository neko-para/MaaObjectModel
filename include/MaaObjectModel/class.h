#pragma once

#include "object.h"
#include "port.h"
#include "type.h"

extern "C"
{
    MResult MAA_API MaaRtInitClass();
    MResult MAA_API MaaRtRegisterClass(const MUUID* uuid, MFactory factory);
    MResult MAA_API MaaRtLocateClass(const MUUID* uuid, MFactory* factory);
}
