/**
 * gbengine.dll - Audio nodes
 * gbSound2DNode and gbSound3DNode (Miles Sound System wrappers)
 */

#include "gbengine/gbAudio.h"

// ======== gbSound2DNode ========

bool gbSound2DNode::IsPlaying(void) {
    /* UNCERTAIN: Check if 2D sound is playing */
    // Would query Miles Sound System sample state
    return false;
}

// ======== gbSound3DNode ========

bool gbSound3DNode::IfAttached(void) {
    /* UNCERTAIN: Check if 3D sound is attached to source */
    // Would check if 3D sample is active in Miles Sound System
    return false;
}
