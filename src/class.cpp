#include "MaaObjectModel.h"

#include <string>
#include <unordered_map>

static std::unordered_map<std::string, MFactory>* pFactory;

MBool MAA_API MaaRtInitClass()
{
    pFactory = new std::unordered_map<std::string, MFactory>();
}

MBool MAA_API MaaRtRegisterClass(const MUUID* uuid, MFactory factory)
{
    if (pFactory->contains(uuid->id)) {
        return 0;
    }
    else {
        (*pFactory)[uuid->id] = factory;
        return 1;
    }
}

MBool MAA_API MaaRtLocateClass(const MUUID* uuid, MFactory* factory)
{
    auto it = pFactory->find(uuid->id);
    if (it == pFactory->end() || !factory) {
        return 0;
    }
    else {
        *factory = it->second;
        return 1;
    }
}
