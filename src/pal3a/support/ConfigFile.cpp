#include "ConfigFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ConfigFile::ConfigFile()
{
    m_filename[0] = '\0';
}

ConfigFile::~ConfigFile()
{
}

void ConfigFile::Open(char *filename)
{
    strncpy(m_filename, filename, 259);
    m_filename[259] = '\0';
}

bool ConfigFile::Read(char *pSection, char *pKey, char **ppValue)
{
    static char buf[256];
    DWORD ret = GetPrivateProfileStringA(pSection, pKey, "", buf, 256, m_filename);
    if (ret == 0)
        return false;
    *ppValue = buf;
    return true;
}

bool ConfigFile::Readn(char *pSection, char *pKey, int *nValue, int nDefaultValue)
{
    char buf[64];
    DWORD ret = GetPrivateProfileStringA(pSection, pKey, "", buf, 64, m_filename);
    if (ret == 0) {
        *nValue = nDefaultValue;
        return false;
    }
    *nValue = atoi(buf);
    return true;
}

bool ConfigFile::Readn(char *pSection, char *pKey, int *nValue)
{
    char buf[64];
    DWORD ret = GetPrivateProfileStringA(pSection, pKey, "", buf, 64, m_filename);
    if (ret == 0)
        return false;
    *nValue = atoi(buf);
    return true;
}

bool ConfigFile::Readf(char *pSection, char *pKey, float *fValue)
{
    char buf[64];
    DWORD ret = GetPrivateProfileStringA(pSection, pKey, "", buf, 64, m_filename);
    if (ret == 0)
        return false;
    *fValue = (float)atof(buf);
    return true;
}

bool ConfigFile::Write(char *pSection, char *pKey, char *pValue)
{
    return WritePrivateProfileStringA(pSection, pKey, pValue, m_filename) != 0;
}

bool ConfigFile::Writen(char *pSection, char *pKey, int nValue)
{
    char buf[64];
    sprintf(buf, "%d", nValue);
    return WritePrivateProfileStringA(pSection, pKey, buf, m_filename) != 0;
}

bool ConfigFile::Writef(char *pSection, char *pKey, float fValue)
{
    char buf[64];
    sprintf(buf, "%f", fValue);
    return WritePrivateProfileStringA(pSection, pKey, buf, m_filename) != 0;
}
