#pragma once
// PAL3 file system RAII helpers

class OpenBaseFile {
public:
    OpenBaseFile(void **pv);
    ~OpenBaseFile();
};

class OpenNULLFile {
public:
    static void *OpenNULLFile_ctor(void **pv);
};
