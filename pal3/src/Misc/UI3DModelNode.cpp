#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UI3DModelNode.h"

// 0x004B74A0
UI3DModelNode::UI3DModelNode()
{
  this->_todo_0E8 = 0;
  this->_todo_064 = 0;
  memset(this->_todo_068, 0, sizeof(this->_todo_068));
  this->_todo_05C = 0;
  this->_todo_060 = 0;
  this->_todo_0F0 = 0;
  this->_todo_0EC = 0;
  this->_todo_0F4 = 0;
}

// 0x004B7510
void UI3DModelNode::_UI3DModelNode()
{
  ((UITextArea *)this)->ReleaseAllTextures();
  gbChain1DNode::Process();
}
