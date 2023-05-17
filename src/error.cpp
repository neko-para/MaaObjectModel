#include "MaaObjectModel.h"

MString hErr = 0;

void MAA_API MaaRtSetLastError(MRString err)
{
    if (hErr) {
        MaaRtDeleteString(hErr);
    }
    hErr = MaaRtCreateString(err, -1);
}

MString MAA_API MaaRtGetLastError()
{
    if (hErr) {
        return hErr;
    }
    else {
        return 0;
    }
}
