#pragma once

#include "port.h"
#include "type.h"

extern "C"
{
    MBool MAA_API MaaRtInitClass();
    MBool MAA_API MaaRtRegisterClass(const MUUID* uuid, MFactory factory);
    MBool MAA_API MaaRtLocateClass(const MUUID* uuid, MFactory* factory);
}
