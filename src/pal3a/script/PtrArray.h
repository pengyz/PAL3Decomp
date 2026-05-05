#ifndef PAL3A_PTRARRAY_H
#define PAL3A_PTRARRAY_H

#include "pal3a_types.h"

class PtrArray {
public:
    char _data[16];

    ~PtrArray();
    void RemoveAt(int nIndex, int nCount);
    void InsertAt(int nIndex, void * newElement, int nCount);
    PtrArray();
    void SetSize(int nNewSize, int nGrowBy);
    void Remove(void * element);
    void SetAtGrow(int nIndex, void * newElement);
};

#endif // PAL3A_PTRARRAY_H
