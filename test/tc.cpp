#define _CRT_SECURE_NO_WARNINGS

#include "tc.h"

#include <iostream>

const MUUID IID_TestClass = { "52a0f0f5-c41e-4760-966c-ba1bd9a2e100" };
const MUUID CID_TestClass = { "f4fa72af-5036-46f0-96c7-349347949b61" };

TestClass::~TestClass()
{
    std::cout << "Destructor called from " << this << std::endl;
}

void TestClass::set(MInt c)
{
    cnt = c;
}

void TestClass::hello()
{
    std::cout << "Hello MAA from " << this << " with " << cnt << std::endl;
}

extern MIUnknown* VT[2];
extern const MUUID* IDS[2];

MAA_DECLARE_QUERY_INTERFACE(TestClass, VT, IDS)
MAA_DECLARE_GET_IIDS(TestClass, VT, IDS)

MResult MAA_CALL set(MHandle self, MInt cnt)
{
    static_cast<TestClass*>(static_cast<MCppInnerObject*>(static_cast<MObject*>(self)->inner)->obj)->set(cnt);
    return ME_OK;
}

MResult MAA_CALL hello(MHandle self)
{
    static_cast<TestClass*>(static_cast<MCppInnerObject*>(static_cast<MObject*>(self)->inner)->obj)->hello();
    return ME_OK;
}

ITestClass MI = { {
                      .QueryInterface = QueryInterfaceTestClass,
                      .AddRef = __AddRef,
                      .Release = __Release,
                      .GetIids = GetIidsTestClass,
                  },
                  set,
                  hello };

MIUnknown* VT[2] = { &MI, &MI };
const MUUID* IDS[2] = { &IID_Unknown, &IID_TestClass };

MAA_DECLARE_CLASS_FACTORY(TestClass, VT, IDS)

void initTestClass()
{
    MaaRtRegisterClass(&CID_TestClass, createTestClass);
}
