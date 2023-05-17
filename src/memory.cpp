#include "MaaObjectModel.h"

MResult MAA_API MaaRtAlloc(MUInt size, MHandle* out)
{
    if (!out) {
        return ME_POINTER;
    }
    *out = new char[size];
    return ME_OK;
}

MResult MAA_API MaaRtFree(MHandle handle)
{
    // TODO: Maybe check?
    if (handle) {
        delete handle;
        return ME_OK;
    }
    else {
        return ME_POINTER;
    }
}
