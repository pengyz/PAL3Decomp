/**
 * gbengine.dll - gbVolModNode
 * Volume modifier node for lighting/shadowing
 */

#include "gbengine/gbVisNode.h"
#include "gbengine/gbSceneGraph.h"
#include <string.h>

gbVolModNode::gbVolModNode(void) {
    memset(this, 0, sizeof(gbVolModNode));
}

gbVolModNode::gbVolModNode(const gbVolModNode& other) {
    memcpy(this, &other, sizeof(gbVolModNode));
}

gbVolModNode::~gbVolModNode(void) {
}

gbVolModNode& gbVolModNode::operator=(const gbVolModNode& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbVolModNode));
    }
    return *this;
}

void gbVolModNode::SetVolModObj(gbVolumeModifier* volmod) {
    /* UNCERTAIN: Volume modifier assignment */
    // Would store pointer to volume modifier object
}

int gbVolModNode::Attach(gbRenderEffect* effect) {
    /* UNCERTAIN: Attach render effect to node */
    return 1;
}

void gbVolModNode::GetBoundSphere(gbSphere* sphere) {
    if (sphere) {
        sphere->center.x = sphere->center.y = sphere->center.z = 0.0f;
        sphere->radius = 100.0f;
    }
}

void gbVolModNode::Render(gbRenderInfoObj* renderInfo) {
    /* UNCERTAIN: Volume modifier rendering */
    // Would render shadow volume or lighting volume
}

gbLightObj* gbVolModNode::GetLightObj(void) {
    /* UNCERTAIN: Get associated light object */
    return NULL;
}
