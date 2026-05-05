#ifndef PAL3A_SEHEXCEPTION_H
#define PAL3A_SEHEXCEPTION_H

#include "pal3a_types.h"

class CSEHException {
public:
    uint m_uiErrCode;
    char m_szExceptionString[260];

    CSEHException();
    CSEHException(uint u);
    CSEHException(char *str, char *filename, int linenum);
    ~CSEHException();
    unsigned int GetErrCode();
    char const *GetErrInfo();
    void SetBounderParam(int bGetFaultReason, int bGetStackTraceString, int bShowRegs, int bLetItCrash, ulong dwOpts);
    void InitCrashBounder();
    void BounderFunc(uint u, _EXCEPTION_POINTERS *pEP);
};

void BounderOutPut(char *s);
void InitBounderFile();

#endif // PAL3A_SEHEXCEPTION_H
