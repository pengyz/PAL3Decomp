#include "3ds.h"

bool CLoad3DS::Import3DS(t3DModel * pModel, char * strFileName)
{
    /* stub */
    return FALSE;
}

void CLoad3DS::ProcessNextMaterialChunk(t3DModel * pModel, tChunk * pPreviousChunk)
{
    /* stub */
}

void CLoad3DS::ComputeNormals(t3DModel * pModel)
{
    /* stub */
}

void CLoad3DS::ReadUVCoordinates(t3DObject * pObject, tChunk * pPreviousChunk)
{
    /* stub */
}

void CLoad3DS::ReadChunk(tChunk * pChunk)
{
    /* stub */
}

void CLoad3DS::ReadObjectMaterial(t3DModel * pModel, t3DObject * pObject, tChunk * pPreviousChunk)
{
    /* stub */
}

void CLoad3DS::ProcessNextChunk(t3DModel * pModel, tChunk * pPreviousChunk)
{
    /* stub */
}

void CLoad3DS::ReadVertexIndices(t3DObject * pObject, tChunk * pPreviousChunk)
{
    /* stub */
}

int CLoad3DS::GetString(char * pBuffer)
{
    /* stub */
    return 0;
}

void CLoad3DS::ReadVertices(t3DObject * pObject, tChunk * pPreviousChunk)
{
    /* stub */
}

void CLoad3DS::CleanUp()
{
    /* stub */
}

void CLoad3DS::ProcessNextObjectChunk(t3DModel * pModel, t3DObject * pObject, tChunk * pPreviousChunk)
{
    /* stub */
}

CLoad3DS::CLoad3DS()
{
    /* stub */
}

void CLoad3DS::ReadColorChunk(tMaterialInfo * pMaterial, tChunk * pChunk)
{
    /* stub */
}

t3DModel::~t3DModel()
{
    /* stub */
}

t3DModel::t3DModel()
{
    /* stub */
}

