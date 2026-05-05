#ifndef PAL3A_CONFIGFILE_H
#define PAL3A_CONFIGFILE_H

#include "pal3a_types.h"

class ConfigFile {
public:
    char m_filename[260];

    ConfigFile();
    ~ConfigFile();
    void Open(char *filename);
    bool Read(char *pSection, char *pKey, char **ppValue);
    bool Readn(char *pSection, char *pKey, int *nValue, int nDefaultValue);
    bool Readn(char *pSection, char *pKey, int *nValue);
    bool Readf(char *pSection, char *pKey, float *fValue);
    bool Write(char *pSection, char *pKey, char *pValue);
    bool Writen(char *pSection, char *pKey, int nValue);
    bool Writef(char *pSection, char *pKey, float fValue);
};

#endif // PAL3A_CONFIGFILE_H
