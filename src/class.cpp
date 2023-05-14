#include "MaaObjectModel.h"

#include <string>
#include <unordered_map>

static std::unordered_map<std::string, MFactory>* pFactory;

extern "C" MResult MAA_API MaaRtInitClass()
{
    pFactory = new std::unordered_map<std::string, MFactory>();
    return ME_OK;
}

extern "C" MResult MAA_API MaaRtRegisterClass(const MUUID* uuid, MFactory factory)
{
    if (pFactory->contains(uuid->id) || !factory) {
        return ME_INVALIDARG;
    }
    else {
        (*pFactory)[uuid->id] = factory;
        return ME_OK;
    }
}

extern "C" MResult MAA_API MaaRtLocateClass(const MUUID* uuid, MFactory* factory)
{
    auto it = pFactory->find(uuid->id);
    if (!factory) {
        return ME_POINTER;
    }
    else if (it == pFactory->end()) {
        return ME_INVALIDARG;
    }
    else {
        *factory = it->second;
        return ME_OK;
    }
}
