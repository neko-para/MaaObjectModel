#pragma once

#include "MaaObjectModel.h"

struct TestClass : public MCppBaseObject
{
    void hello(MInt cnt);
};

struct ITestClass : public MIUnknown
{
    MResult(MAA_CALL* hello)(MHandle self, MInt cnt);
};

extern const MUUID IID_TestClass;
extern const MUUID CID_TestClass;

void initTestClass();
