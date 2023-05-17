#include "MaaObjectModel.h"

MString hErr = 0;

MResult MAA_API MaaRtSetLastError(MRString err)
{
    if (hErr) {
        MaaRtDeleteString(hErr);
    }
    hErr = MaaRtCreateString(err, -1);
    return ME_OK;
}

MResult MAA_API MaaRtGetLastError(MString* err)
{
    if (!err) {
        return ME_POINTER;
    }
    if (hErr) {
        *err = MaaRtDuplicateString(hErr);
        return ME_OK;
    }
    else {
        return ME_NODATA;
    }
}
