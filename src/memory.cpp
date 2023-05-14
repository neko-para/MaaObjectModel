#include "MaaObjectModel.h"

MHandle MAA_API MaaRtAlloc(MUInt size)
{
    return new char[size];
}

void MAA_API MaaRtFree(MHandle handle)
{
    delete handle;
}
