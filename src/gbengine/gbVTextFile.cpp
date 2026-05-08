#include "gbengine/gbengine_internal.h"
#include "gbengine/gbVFileSystem.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern gbVFileSystem* g_pVFileSys;

// 0x10030fe0
gbVTextFile::~gbVTextFile() {
    gbVFile* pFile = m_pFile;
    int type = g_pVFileSys->Type;
    if (type == 1) {
        if (pFile != NULL) {
            g_pVFileSys->m_cpk.Close(&pFile->cpkFile);
            return;
        }
        g_pVFileSys->m_cpk.Close(NULL);
        return;
    }
    if (type == 0) {
        fclose((FILE*)pFile->fp);
        pFile->flags = 0;
        return;
    }
    if (type == 2) {
        free(pFile->fp);
        pFile->flags = 0;
    }
}

// 0x10031050
void gbVTextFile::Open(char* filename) {
    gbVFile* pFile = m_pFile;
    if (pFile != NULL) {
        int type = g_pVFileSys->Type;
        if (type == 1) {
            if (pFile == NULL) {
                g_pVFileSys->m_cpk.Close(NULL);
            } else {
                g_pVFileSys->m_cpk.Close(&pFile->cpkFile);
            }
        } else if (type == 0) {
            fclose((FILE*)pFile->fp);
            pFile->flags = 0;
        } else if (type == 2) {
            free(pFile->fp);
            pFile->flags = 0;
        }
        m_pFile = NULL;
    }
    m_pFile = g_pVFileSys->OpenFile(filename, 0x401);
}

// 0x100310e0
void gbVTextFile::Close() {
    gbVFile* pFile = m_pFile;
    if (pFile == NULL) {
        return;
    }
    int type = g_pVFileSys->Type;
    if (type == 1) {
        if (pFile == NULL) {
            g_pVFileSys->m_cpk.Close(NULL);
            m_pFile = NULL;
            return;
        }
        g_pVFileSys->m_cpk.Close(&pFile->cpkFile);
        m_pFile = NULL;
        return;
    }
    if (type == 0) {
        fclose((FILE*)pFile->fp);
    } else if (type == 2) {
        free(pFile->fp);
    } else {
        m_pFile = NULL;
        return;
    }
    pFile->flags = 0;
    m_pFile = NULL;
}

void gbVTextFile::Rewind() {
    if (m_pFile && g_pVFileSys) {
        g_pVFileSys->Rewind(m_pFile);
    }
}

