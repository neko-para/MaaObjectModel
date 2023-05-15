#include "tc.h"

#include <iostream>

int main()
{
    MaaRtInitClass();
    initTestClass();

    MFactory tcf;
    MaaRtLocateClass(&CID_TestClass, &tcf);
    MHandle obj;
    tcf(&IID_Unknown, &obj);
    auto ou = static_cast<MObjectTyped<MIUnknown>*>(obj);

    MUInt size;
    MUUID* iids;
    ou->vptr->GetIids(ou, &size, &iids);
    std::cout << "Get " << size << " IID" << std::endl;

    MHandle iobj;
    ou->vptr->QueryInterface(ou, &iids[1], &iobj);

    MaaRtFree(iids);

    ou->vptr->Release(ou);
    auto ot = static_cast<MObjectTyped<ITestClass>*>(iobj);
    ot->vptr->set(ot, 4);
    ot->vptr->hello(ot);
    ot->vptr->Release(ot);
    return 0;
}
