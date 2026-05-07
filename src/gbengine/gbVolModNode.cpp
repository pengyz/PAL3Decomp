/**
 * gbengine.dll - gbVolModNode
 * Volume modifier node for lighting/shadowing
 */

#include "gbengine/gbengine_internal.h"
#include "gbengine/gbVisNode.h"
#include "gbengine/gbSceneGraph.h"
#include <string.h>

gbVolModNode::~gbVolModNode(void) {
}

void gbVolModNode::SetVolModObj(class gbVolumeModifier * p0) {
    p0->refCount++;
    pVolMod = p0;
}

void gbVolModNode::GetBoundSphere(struct gbSphere * p0) {
    // GetBoundSphere at 0x10013160:
    // Call pVolMod virtual GetBoundSphere to get sphere data,
    // then transform center by localMatrix
    if (pVolMod != 0 && p0 != 0) {
        const gbSphere* src = pVolMod->GetBoundSphere();
        if (src) {
            p0->radius = src->radius;
            localMatrix.Transform((gbVec3D*)&src->center, &p0->center);
        }
    }
}

