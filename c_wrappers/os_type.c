#include "VBoxCAPIGlue.h"

// Wrapper declared in vbox.c
HRESULT GoVboxFAILED(HRESULT result);

HRESULT GoVboxGetGuestOSTypes(IVirtualBox* cbox, IGuestOSType*** ctypes,
    ULONG* typeCount) {
  SAFEARRAY *safeArray = g_pVBoxFuncs->pfnSafeArrayOutParamAlloc();
  HRESULT result = IVirtualBox_GetGuestOSTypes(cbox,
      ComSafeArrayAsOutIfaceParam(safeArray, IGuestOSType *));
  g_pVBoxFuncs->pfnSafeArrayCopyOutIfaceParamHelper(
      (IUnknown ***)ctypes, typeCount, safeArray);
  g_pVBoxFuncs->pfnSafeArrayDestroy(safeArray);
  return result;
}

HRESULT GoVboxGetGuestOSTypeId(IGuestOSType* ctype, char** cid) {
  BSTR wid = NULL;
  HRESULT result = IGuestOSType_GetId(ctype, &wid);
  if (FAILED(result))
    return result;

  g_pVBoxFuncs->pfnUtf16ToUtf8(wid, cid);
  g_pVBoxFuncs->pfnComUnallocString(wid);
  return result;
}
HRESULT GoVboxIGuestOSTypeRelease(IGuestOSType* ctype) {
  return IGuestOSType_Release(ctype);
}
