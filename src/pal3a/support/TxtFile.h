#ifndef PAL3A_TXTFILE_H
#define PAL3A_TXTFILE_H

#include "pal3a_types.h"

class TxtFile {
public:
    char m_token[512];
    char *m_buf;
    char *m_sectionstart;
    char *m_curpos;

    TxtFile();
    ~TxtFile();
    void Load(char *filename);
    void Destroy();
    void OpenSection(char *name);
    void RewindSection();
    int NextToken();
    void NextValueToken();
    float GetTokenValue(char *name);
    bool GetTokenValue_String(char *name, char *buffer, int bufferlen);
};

#endif // PAL3A_TXTFILE_H
