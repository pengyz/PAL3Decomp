#pragma once
// Auto-generated: t3DObject

class D3DXVECTOR2;
class D3DXVECTOR3;
class tFace;

class t3DObject {
public:
    int numOfVerts; // +0x0
    int numOfFaces; // +0x4
    int numTexVertex; // +0x8
    int materialID; // +0xC
    unsigned char bHasTexture; // +0x10
    char strName[255]; // +0x11
    D3DXVECTOR3 * pVerts; // +0x110
    D3DXVECTOR3 * pNormals; // +0x114
    D3DXVECTOR2 * pTexVerts; // +0x118
    tFace * pFaces; // +0x11C
    // total size: 0x120 (288)

};
