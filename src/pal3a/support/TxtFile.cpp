#include "TxtFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TxtFile::TxtFile()
{
    m_token[0] = '\0';
    m_buf = NULL;
    m_sectionstart = NULL;
    m_curpos = NULL;
}

TxtFile::~TxtFile()
{
    Destroy();
}

void TxtFile::Load(char *filename)
{
    Destroy();

    FILE *fp = fopen(filename, "rb");
    if (!fp)
        return;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    m_buf = new char[size + 1];
    fread(m_buf, 1, size, fp);
    m_buf[size] = '\0';
    fclose(fp);

    m_curpos = m_buf;
    m_sectionstart = m_buf;
}

void TxtFile::Destroy()
{
    if (m_buf) {
        delete[] m_buf;
        m_buf = NULL;
    }
    m_curpos = NULL;
    m_sectionstart = NULL;
    m_token[0] = '\0';
}

void TxtFile::OpenSection(char *name)
{
    if (!m_buf)
        return;

    char sectag[256];
    sprintf(sectag, "[%s]", name);
    int taglen = (int)strlen(sectag);

    char *p = m_buf;
    while (*p) {
        if (*p == '[') {
            if (strncmp(p, sectag, taglen) == 0) {
                p += taglen;
                while (*p == '\r' || *p == '\n')
                    p++;
                m_sectionstart = p;
                m_curpos = p;
                return;
            }
        }
        while (*p && *p != '\n')
            p++;
        if (*p == '\n')
            p++;
    }
}

void TxtFile::RewindSection()
{
    if (m_sectionstart)
        m_curpos = m_sectionstart;
}

int TxtFile::NextToken()
{
    if (!m_curpos || !*m_curpos)
        return 0;

    // Skip whitespace
    while (*m_curpos == ' ' || *m_curpos == '\t' || *m_curpos == '\r' || *m_curpos == '\n') {
        m_curpos++;
    }

    if (*m_curpos == '\0' || *m_curpos == '[')
        return 0;

    // Skip comments
    if (*m_curpos == '/' && *(m_curpos + 1) == '/') {
        while (*m_curpos && *m_curpos != '\n')
            m_curpos++;
        return NextToken();
    }

    // Read token
    int i = 0;
    if (*m_curpos == '\"') {
        m_curpos++;
        while (*m_curpos && *m_curpos != '\"' && i < 511) {
            m_token[i++] = *m_curpos++;
        }
        if (*m_curpos == '\"')
            m_curpos++;
    } else {
        while (*m_curpos && *m_curpos != ' ' && *m_curpos != '\t' &&
               *m_curpos != '\r' && *m_curpos != '\n' && *m_curpos != '=' && i < 511) {
            m_token[i++] = *m_curpos++;
        }
    }
    m_token[i] = '\0';

    return 1;
}

void TxtFile::NextValueToken()
{
    if (!m_curpos)
        return;

    // Skip to '=' or end of line
    while (*m_curpos && *m_curpos != '=' && *m_curpos != '\n')
        m_curpos++;

    if (*m_curpos == '=')
        m_curpos++;

    // Skip whitespace (not newline)
    while (*m_curpos == ' ' || *m_curpos == '\t')
        m_curpos++;

    // Read value token
    int i = 0;
    if (*m_curpos == '\"') {
        m_curpos++;
        while (*m_curpos && *m_curpos != '\"' && *m_curpos != '\n' && i < 511) {
            m_token[i++] = *m_curpos++;
        }
        if (*m_curpos == '\"')
            m_curpos++;
    } else {
        while (*m_curpos && *m_curpos != '\r' && *m_curpos != '\n' &&
               *m_curpos != ' ' && *m_curpos != '\t' && i < 511) {
            m_token[i++] = *m_curpos++;
        }
    }
    m_token[i] = '\0';
}

float TxtFile::GetTokenValue(char *name)
{
    char *saved = m_curpos;
    m_curpos = m_sectionstart;

    while (NextToken()) {
        if (strcmp(m_token, name) == 0) {
            NextValueToken();
            float val = (float)atof(m_token);
            return val;
        }
        // Skip to next line
        while (*m_curpos && *m_curpos != '\n')
            m_curpos++;
        if (*m_curpos == '\n')
            m_curpos++;
        if (*m_curpos == '[')
            break;
    }

    m_curpos = saved;
    return 0.0f;
}

bool TxtFile::GetTokenValue_String(char *name, char *buffer, int bufferlen)
{
    char *saved = m_curpos;
    m_curpos = m_sectionstart;

    while (NextToken()) {
        if (strcmp(m_token, name) == 0) {
            NextValueToken();
            strncpy(buffer, m_token, bufferlen - 1);
            buffer[bufferlen - 1] = '\0';
            return true;
        }
        while (*m_curpos && *m_curpos != '\n')
            m_curpos++;
        if (*m_curpos == '\n')
            m_curpos++;
        if (*m_curpos == '[')
            break;
    }

    m_curpos = saved;
    return false;
}
