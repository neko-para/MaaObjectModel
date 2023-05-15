#pragma once

#include "MaaObjectModel.h"

struct TestClass : public MCppBaseObject
{
    MInt cnt;

    virtual ~TestClass();
    void set(MInt c);
    void hello();
};

struct ITestClass : public MIUnknown
{
    MResult(MAA_CALL* set)(MHandle self, MInt cnt);
    MResult(MAA_CALL* hello)(MHandle self);
};

extern const MUUID IID_TestClass;
extern const MUUID CID_TestClass;

void initTestClass();
