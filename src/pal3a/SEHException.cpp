#include "SEHException.h"
#include <stdio.h>
#include <string.h>

static FILE *g_bounderFile = NULL;

CSEHException::CSEHException()
{
    m_uiErrCode = 0;
    m_szExceptionString[0] = '\0';
}

CSEHException::CSEHException(uint u)
{
    m_uiErrCode = u;
    sprintf(m_szExceptionString, "SEH Exception: 0x%08X", u);
}

CSEHException::CSEHException(char *str, char *filename, int linenum)
{
    m_uiErrCode = 0;
    sprintf(m_szExceptionString, "%s (%s:%d)", str, filename, linenum);
}

CSEHException::~CSEHException()
{
}

unsigned int CSEHException::GetErrCode()
{
    return m_uiErrCode;
}

char const *CSEHException::GetErrInfo()
{
    return m_szExceptionString;
}

void CSEHException::SetBounderParam(int bGetFaultReason, int bGetStackTraceString, int bShowRegs, int bLetItCrash, ulong dwOpts)
{
}

void CSEHException::InitCrashBounder()
{
}

void CSEHException::BounderFunc(uint u, _EXCEPTION_POINTERS *pEP)
{
    m_uiErrCode = u;
    sprintf(m_szExceptionString, "Exception 0x%08X at address 0x%08X",
            u, pEP ? (uint)pEP->ExceptionRecord->ExceptionAddress : 0);
    BounderOutPut(m_szExceptionString);
}

void InitBounderFile()
{
    if (!g_bounderFile)
        g_bounderFile = fopen("bounder.log", "w");
}

void BounderOutPut(char *s)
{
    if (g_bounderFile) {
        fprintf(g_bounderFile, "%s\n", s);
        fflush(g_bounderFile);
    }
}
