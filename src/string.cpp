#include "MaaObjectModel.h"

#include <cstring>

struct MIString : public MIUnknown
{};

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
        *out = self;
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

static MIString MI = {
    { .QueryInterface = __QueryInterface, .AddRef = __AddRef, .Release = __Release, .GetIids = __GetIids }
};

extern "C" MString MAA_API MaaRtCreateString(const MChar* str, MInt len)
{
    return new MCppObject { { .vptr = &MI }, new MOString(str, len) };
}

extern "C" MResult MAA_API MaaRtDeleteString(MString str)
{
    static_cast<MCppObject*>(str)->vptr->Release(str);
    return ME_OK;
}

extern "C" MString MAA_API MaaRtDuplicateString(MString str)
{
    static_cast<MCppObject*>(str)->vptr->AddRef(str);
    return str;
}

extern "C" MRString MAA_API MaaRtGetStringData(MString str, MInt* len)
{
    auto p = static_cast<MOString*>(static_cast<MCppObject*>(str)->obj);
    if (len) {
        *len = p->len;
    }
    return p->buf;
}
