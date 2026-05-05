#include "gbengine/gbengine_internal.h"
#include "gbengine/gbVFileSystem.h"
#include <string.h>

// gbVTextFile - Text file reader with line buffering

extern gbVFileSystem* g_pVFileSys;

gbVTextFile::gbVTextFile() {
    lineBuf[0] = '\0';
    m_pFile = NULL;
}

gbVTextFile::gbVTextFile(char* filename) {
    lineBuf[0] = '\0';
    m_pFile = NULL;
    if (filename) {
        Open(filename);
    }
}

gbVTextFile::~gbVTextFile() {
    Close();
}

gbVTextFile& gbVTextFile::operator=(const gbVTextFile& other) {
    if (this != &other) {
        Close();
        memcpy(lineBuf, other.lineBuf, sizeof(lineBuf));
        m_pFile = other.m_pFile;
    }
    return *this;
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

char* gbVTextFile::ReadLine() {
    if (!m_pFile || !g_pVFileSys) {
        return NULL;
    }

    // Read a line from the file
    char* result = g_pVFileSys->ReadLine(lineBuf, sizeof(lineBuf) - 1, m_pFile);
    if (!result) {
        return NULL;
    }

    // Trim trailing newline/carriage return
    int len = (int)strlen(lineBuf);
    while (len > 0 && (lineBuf[len - 1] == '\n' || lineBuf[len - 1] == '\r')) {
        lineBuf[--len] = '\0';
    }

    return lineBuf;
}
