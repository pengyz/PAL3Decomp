#include "gbengine/gbVisNode.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbVolModNode::gbVolModNode(gbVolModNode const & p1) {}

gbVolModNode::gbVolModNode() {}

gbLightObj * gbVolModNode::GetLightObj() { return 0; }

gbVolModNode & gbVolModNode::operator=(gbVolModNode const & p1) { static gbVolModNode _d; return _d; }

gbVolModNode::~gbVolModNode() {}

int gbVolModNode::Attach(gbRenderEffect * p1) { return 0; }

void gbVolModNode::GetBoundSphere(gbSphere * p1) { }

void gbVolModNode::Render(gbRenderInfoObj * p1) { }

void gbVolModNode::SetVolModObj(gbVolumeModifier * p1) { }

