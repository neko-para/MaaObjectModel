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

static MBool MAA_CALL __QueryInterface(MHandle self, const MUUID* iid, MHandle* out)
{
    if (!out) {
        return 0;
    }
    if (!strcmp(iid->id, IID_Unknown.id)) {
        *out = self;
        return 1;
    }
    else {
        return 0;
    }
}

static MBool MAA_CALL __GetIids(MHandle self, MUInt* size, MUUID* out)
{
    if (size) {
        *size = 0;
        return 1;
    }
    else {
        return 0;
    }
}

static MIString MI = {
    { .QueryInterface = __QueryInterface, .AddRef = __AddRef, .Release = __Release, .GetIids = __GetIids }
};

MString MAA_API MaaRtCreateString(const MChar* str, MInt len)
{
    return new MCppObject { { .vptr = &MI }, new MOString(str, len) };
}

void MAA_API MaaRtDeleteString(MString str)
{
    static_cast<MCppObject*>(str)->vptr->Release(str);
}

MString MAA_API MaaRtDuplicateString(MString str)
{
    static_cast<MCppObject*>(str)->vptr->AddRef(str);
    return str;
}

MRString MAA_API MaaRtGetStringData(MString str, MInt* len)
{
    auto p = static_cast<MOString*>(static_cast<MCppObject*>(str)->obj);
    if (len) {
        *len = p->len;
    }
    return p->buf;
}
