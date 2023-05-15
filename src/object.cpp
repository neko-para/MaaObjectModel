#include "MaaObjectModel.h"

MUInt MAA_API __AddRef(MHandle self)
{
    auto* p = static_cast<MObject*>(self);
    return ++p->inner->ref;
}

MUInt MAA_API __Release(MHandle self)
{
    auto* p = static_cast<MCppInnerObject*>(static_cast<MObject*>(self)->inner);
    auto ref = --p->ref;
    if (ref == 0) {
        delete p->obj;
        delete[] p->vptrs;
        delete p;
        return 0;
    }
    else {
        return ref;
    }
}
