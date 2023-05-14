#include "MaaObjectModel.h"

MUInt MAA_CALL __AddRef(MHandle self)
{
    MCppObject* p = static_cast<MCppObject*>(self);
    return ++p->ref;
}

MUInt MAA_CALL __Release(MHandle self)
{
    MCppObject* p = static_cast<MCppObject*>(self);
    auto ref = --p->ref;
    if (ref == 0) {
        delete p->obj;
        delete p;
        return 0;
    }
    else {
        return ref;
    }
}
