#ifndef PAL3A_3DS_H
#define PAL3A_3DS_H

#include "pal3a_types.h"

class CLoad3DS {
public:
    char _data[200004];

    bool Import3DS(t3DModel * pModel, char * strFileName);
    void ProcessNextMaterialChunk(t3DModel * pModel, tChunk * pPreviousChunk);
    void ComputeNormals(t3DModel * pModel);
    void ReadUVCoordinates(t3DObject * pObject, tChunk * pPreviousChunk);
    void ReadChunk(tChunk * pChunk);
    void ReadObjectMaterial(t3DModel * pModel, t3DObject * pObject, tChunk * pPreviousChunk);
    void ProcessNextChunk(t3DModel * pModel, tChunk * pPreviousChunk);
    void ReadVertexIndices(t3DObject * pObject, tChunk * pPreviousChunk);
    int GetString(char * pBuffer);
    void ReadVertices(t3DObject * pObject, tChunk * pPreviousChunk);
    void CleanUp();
    void ProcessNextObjectChunk(t3DModel * pModel, t3DObject * pObject, tChunk * pPreviousChunk);
    CLoad3DS();
    void ReadColorChunk(tMaterialInfo * pMaterial, tChunk * pChunk);
};

class t3DModel {
public:
    char _data[40];

    ~t3DModel();
    t3DModel();
};

#endif // PAL3A_3DS_H
