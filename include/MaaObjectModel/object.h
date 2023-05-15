#pragma once

#include "port.h"
#include "type.h"

#include <atomic>

struct MIUnknown
{
    MResult(MAA_CALL* QueryInterface)(MHandle self, const MUUID* iid, MHandle* out);
    MUInt(MAA_CALL* AddRef)(MHandle self);
    MUInt(MAA_CALL* Release)(MHandle self);
    MResult(MAA_CALL* GetIids)(MHandle self, MUInt* size, MUUID* out);
};

struct MInnerObject;

struct MObject
{
    MIUnknown* vptr;
    MInnerObject* inner;
};

struct MCppBaseObject
{
    virtual ~MCppBaseObject() = default;
};

struct MInnerObject
{
    std::atomic<MUInt> ref;
    MObject* vptrs;
};

struct MCppInnerObject : public MInnerObject
{
    MCppBaseObject* obj;
};

MUInt MAA_API __AddRef(MHandle self);
MUInt MAA_API __Release(MHandle self);

using MFactory = MResult(MAA_CALL*)(const MUUID* iid, MHandle* out);
