#include "tc.h"

int main()
{
    MaaRtInitClass();
    initTestClass();

    MFactory tcf;
    MaaRtLocateClass(&CID_TestClass, &tcf);
    MHandle obj;
    tcf(&IID_TestClass, &obj);
    static_cast<ITestClass*>(static_cast<MObject*>(obj)->vptr)->hello(obj, 4);
    return 0;
}
