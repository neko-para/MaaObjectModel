#define _CRT_SECURE_NO_WARNINGS

#include "tc.h"

#include <iostream>

const MUUID IID_TestClass = { "52a0f0f5-c41e-4760-966c-ba1bd9a2e100" };
const MUUID CID_TestClass = { "f4fa72af-5036-46f0-96c7-349347949b61" };

void TestClass::hello(MInt cnt)
{
    std::cout << "Hello MAA from " << this << " with " << cnt << std::endl;
}

static MResult MAA_CALL __QueryInterface(MHandle self, const MUUID* iid, MHandle* out)
{
    if (!out || !iid) {
        return ME_POINTER;
    }
    auto* p = static_cast<MObject*>(self);
    if (!strcmp(iid->id, IID_Unknown.id)) {
        p->vptr->AddRef(p);
        *out = &p->inner->vptrs[0];
        return ME_OK;
    }
    else if (!strcmp(iid->id, IID_TestClass.id)) {
        p->vptr->AddRef(p);
        *out = &p->inner->vptrs[1];
        return ME_OK;
    }
    else {
        return ME_NOINTERFACE;
    }
}

static MResult MAA_CALL __GetIids([[maybe_unused]] MHandle self, MUInt* size, MUUID* out)
{
    if (size && out) {
        *size = 1;
        strcpy(out[0].id, IID_TestClass.id);
        return ME_OK;
    }
    else {
        return ME_POINTER;
    }
}

MResult MAA_CALL hello(MHandle self, MInt cnt)
{
    static_cast<TestClass*>(static_cast<MCppInnerObject*>(static_cast<MObject*>(self)->inner)->obj)->hello(cnt);
    return ME_OK;
}

ITestClass MI = { {
                      .QueryInterface = __QueryInterface,
                      .AddRef = __AddRef,
                      .Release = __Release,
                      .GetIids = __GetIids,
                  },
                  hello };

MResult MAA_CALL createTestClass(const MUUID* iid, MHandle* out)
{
    if (!out) {
        return ME_POINTER;
    }
    auto res = new MCppInnerObject { 1, new MObject[2], new TestClass() };
    res->vptrs[0].vptr = &MI;
    res->vptrs[0].inner = res;
    res->vptrs[1].vptr = &MI;
    res->vptrs[1].inner = res;
    *out = &res->vptrs[0];
    if (!strcmp(iid->id, IID_Unknown.id)) {
        *out = &res->vptrs[0];
        return ME_OK;
    }
    else if (!strcmp(iid->id, IID_TestClass.id)) {
        *out = &res->vptrs[1];
        return ME_OK;
    }
    else {
        delete res->obj;
        delete[] res->vptrs;
        delete res;
        return ME_NOINTERFACE;
    }
}

void initTestClass()
{
    MaaRtRegisterClass(&CID_TestClass, createTestClass);
}
