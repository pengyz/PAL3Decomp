#include "gbengine/gbengine_internal.h"
#include "gbengine/gbVFileSystem.h"
#include <string.h>

// gbVTextFile - Text file reader with line buffering

extern gbVFileSystem* g_pVFileSys;

gbVTextFile::~gbVTextFile() {
    /* STUB */
    Close();
}

void gbVTextFile::Open(char* filename) {
    if (!filename || !g_pVFileSys) {
        return;
    }

    Close();
    m_pFile = g_pVFileSys->OpenFile(filename, 0);
}

void gbVTextFile::Close() {
    if (m_pFile && g_pVFileSys) {
        g_pVFileSys->CloseFile(m_pFile);
        m_pFile = NULL;
    }
}

void gbVTextFile::Rewind() {
    if (m_pFile && g_pVFileSys) {
        g_pVFileSys->Rewind(m_pFile);
    }
}

