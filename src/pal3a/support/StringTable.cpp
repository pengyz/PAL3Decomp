#include "StringTable.h"
#include <stdio.h>
#include <string.h>

StringTable::StringTable()
{
}

StringTable::~StringTable()
{
}

void StringTable::Load(char *filename)
{
    m_data.clear();

    FILE *fp = fopen(filename, "r");
    if (!fp)
        return;

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        // Remove trailing newline
        int len = (int)strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
            line[--len] = '\0';

        // Skip empty lines and comments
        if (line[0] == '\0' || line[0] == '/' || line[0] == '#')
            continue;

        // Find separator (= or tab)
        char *sep = strchr(line, '=');
        if (!sep)
            sep = strchr(line, '\t');
        if (!sep)
            continue;

        *sep = '\0';
        char *key = line;
        char *val = sep + 1;

        // Trim key
        while (*key == ' ' || *key == '\t')
            key++;
        char *kend = sep - 1;
        while (kend > key && (*kend == ' ' || *kend == '\t'))
            *kend-- = '\0';

        // Trim value
        while (*val == ' ' || *val == '\t')
            val++;

        m_data[key] = val;
    }

    fclose(fp);
}

const char *StringTable::operator[](const char *key)
{
    std::map<std::string, std::string>::iterator it = m_data.find(key);
    if (it != m_data.end())
        return it->second.c_str();
    return "";
}
