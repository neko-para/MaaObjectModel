#pragma once

#include "port.h"
#include "type.h"

#include <atomic>

struct MIUnknown
{
    MBool(MAA_CALL* QueryInterface)(MHandle self, const MUUID* iid, MHandle* out);
    MUInt(MAA_CALL* AddRef)(MHandle self);
    MUInt(MAA_CALL* Release)(MHandle self);
    MBool(MAA_CALL* GetIids)(MHandle self, MUInt* size, MUUID* out);
};

struct MObject
{
    MIUnknown* vptr;
    std::atomic<MUInt> ref;
};

struct MCppBaseObject
{
    virtual ~MCppBaseObject() = default;
};

struct MCppObject : public MObject
{
    MCppBaseObject* obj;
};

MUInt MAA_CALL __AddRef(MHandle self);
MUInt MAA_CALL __Release(MHandle self);

using MFactory = MBool(MAA_CALL*)(MHandle* out);
