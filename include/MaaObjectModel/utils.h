#pragma once

#define MAA_DECLARE_CLASS_FACTORY(CLASS, VTABLE, IIDS)                       \
    static MResult MAA_CALL create##CLASS(const MUUID* iid, MHandle* out)    \
    {                                                                        \
        if (!out) {                                                          \
            return ME_POINTER;                                               \
        }                                                                    \
        constexpr auto len = (sizeof VTABLE) / (sizeof VTABLE[0]);           \
        auto res = new MCppInnerObject { 1, new MObject[len], new CLASS() }; \
        for (MUInt i = 0; i < len; i++) {                                    \
            res->vptrs[i] = { VTABLE[i], res };                              \
        }                                                                    \
        for (auto i = 0; i < len; i++) {                                     \
            if (!strcmp(iid->id, IIDS[i]->id)) {                             \
                *out = res->vptrs + i;                                       \
                return ME_OK;                                                \
            }                                                                \
        }                                                                    \
        delete res->obj;                                                     \
        delete[] res->vptrs;                                                 \
        delete res;                                                          \
        return ME_NOINTERFACE;                                               \
    }

#define MAA_DECLARE_QUERY_INTERFACE(CLASS, VTABLE, IIDS)                                        \
    static MResult MAA_CALL QueryInterface##CLASS(MHandle self, const MUUID* iid, MHandle* out) \
    {                                                                                           \
        if (!out || !iid) {                                                                     \
            return ME_POINTER;                                                                  \
        }                                                                                       \
        constexpr auto len = (sizeof VTABLE) / (sizeof VTABLE[0]);                              \
        auto* p = static_cast<MObject*>(self);                                                  \
        for (MUInt i = 0; i < len; i++) {                                                       \
            if (!strcmp(iid->id, IIDS[i]->id)) {                                                \
                p->vptr->AddRef(p);                                                             \
                *out = p->inner->vptrs + i;                                                     \
                return ME_OK;                                                                   \
            }                                                                                   \
        }                                                                                       \
        return ME_NOINTERFACE;                                                                  \
    }

#define MAA_DECLARE_GET_IIDS(CLASS, VTABLE, IIDS)                                                   \
    static MResult MAA_CALL GetIids##CLASS([[maybe_unused]] MHandle self, MUInt* size, MUUID** out) \
    {                                                                                               \
        if (size && out) {                                                                          \
            constexpr auto len = (sizeof VTABLE) / (sizeof VTABLE[0]);                              \
            *size = len;                                                                            \
            MUUID* res = static_cast<MUUID*>(MaaRtAlloc(sizeof MUUID * len));                       \
            *out = res;                                                                             \
            for (MUInt i = 0; i < len; i++) {                                                       \
                strcpy(res[i].id, IIDS[i]->id);                                                     \
            }                                                                                       \
            return ME_OK;                                                                           \
        }                                                                                           \
        return ME_POINTER;                                                                          \
    }
