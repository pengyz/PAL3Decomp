/**
 * gbengine.dll - gbVolModNode
 * Volume modifier node for lighting/shadowing
 */

#include "gbengine/gbengine_internal.h"
#include "gbengine/gbVisNode.h"
#include "gbengine/gbSceneGraph.h"
#include <string.h>

struct gbRefObject {
    void* vtable;
    int RefCount;
};

gbVolModNode::~gbVolModNode(void) {
}

void gbVolModNode::SetVolModObj(class gbVolumeModifier * p0) {
    if (p0 != 0) {
        ((gbRefObject*)p0)->RefCount += 1;
    }
    pVolMod = (void*)p0;
}

void gbVolModNode::GetBoundSphere(struct gbSphere * p0) {
    // From Ghidra (GetBoundSphere at 0x10013160):
    // Call pVolMod->vtable[2] to get bounding sphere data,
    // then transform center by localMatrix
    if (pVolMod != 0 && p0 != 0) {
        typedef void* (__thiscall *GetSphereFn)(void*);
        int** vt = (int**)pVolMod;
        GetSphereFn fn = (GetSphereFn)((*vt)[2]);
        int* sphereData = (int*)fn(pVolMod);
        if (sphereData) {
            // First dword is radius
            *(int*)&p0->radius = sphereData[0];
            // Transform center by localMatrix
            gbVec3D* srcCenter = (gbVec3D*)(sphereData + 1);
            localMatrix.Transform(srcCenter, &p0->center);
        }
    }
}

