#ifndef PAL3A_CJ_FINDFILE_H
#define PAL3A_CJ_FINDFILE_H

#include "pal3a_types.h"

class CJ_FindFile {
public:
    char _data[988];

    char * _GetFilePath();
    char * _GetFileTitle();
    int _IsDirectory();
    unsigned long _GetLength();
    int _GetFileCreationTime(_FILETIME * time);
    int _MatchesMask(ulong dwMask);
    ~CJ_FindFile();
    int _FindFile(char * pstrName);
    void _CloseFind();
    int _GetFileAccessTime(_FILETIME * time);
    char * _GetFileName();
    char * _GetFileRoot();
    CJ_FindFile();
    int _FindNextFile();
    unsigned long _GetFileSize();
    int _GetFileLastWriteTime(_FILETIME * time);
    int _IsDots();
    char * _GetFileURL();
};

#endif // PAL3A_CJ_FINDFILE_H
