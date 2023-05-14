#include "MaaObjectModel.h"

extern "C" MHandle MAA_API MaaRtAlloc(MUInt size)
{
    return new char[size];
}

extern "C" MResult MAA_API MaaRtFree(MHandle handle)
{
    // TODO: Maybe check?
    delete handle;
    return ME_OK;
}
