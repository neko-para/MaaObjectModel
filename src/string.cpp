#include "MaaObjectModel.h"

#include <cstring>

struct MOString : public MCppBaseObject
{
    MInt len;
    MChar* buf;

    MOString(const MChar* s, MInt l)
    {
        if (l == -1) {
            l = strlen(s);
        }
        len = l;
        buf = new MChar[len + 1];
        memcpy(buf, s, len);
        buf[len] = 0;
    }
    virtual ~MOString() { delete[] buf; }
};

static MResult MAA_CALL __QueryInterface(MHandle self, const MUUID* iid, MHandle* out)
{
    if (!out || !iid) {
        return ME_POINTER;
    }
    if (!strcmp(iid->id, IID_Unknown.id)) {
        *out = MaaRtDuplicateString(self);
        return ME_OK;
    }
    else {
        return ME_NOINTERFACE;
    }
}

static MResult MAA_CALL __GetIids([[maybe_unused]] MHandle self, MUInt* size, [[maybe_unused]] MUUID* out)
{
    if (size) {
        *size = 0;
        return ME_OK;
    }
    else {
        return ME_POINTER;
    }
}

static MIUnknown MI = {
    .QueryInterface = __QueryInterface, .AddRef = __AddRef, .Release = __Release, .GetIids = __GetIids
};

extern "C" MString MAA_API MaaRtCreateString(const MChar* str, MInt len)
{
    auto res = new MCppInnerObject { 1, new MObject[1], new MOString(str, len) };
    res->vptrs[0].vptr = &MI;
    res->vptrs[0].inner = res;
    return &res->vptrs[0];
}

extern "C" MResult MAA_API MaaRtDeleteString(MString str)
{
    static_cast<MObject*>(str)->vptr->Release(str);
    return ME_OK;
}

extern "C" MString MAA_API MaaRtDuplicateString(MString str)
{
    static_cast<MObject*>(str)->vptr->AddRef(str);
    return str;
}

extern "C" MRString MAA_API MaaRtGetStringData(MString str, MInt* len)
{
    auto p = static_cast<MOString*>(static_cast<MCppInnerObject*>(static_cast<MObject*>(str)->inner)->obj);
    if (len) {
        *len = p->len;
    }
    return p->buf;
}
