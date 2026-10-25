#include <stdio.h>
#include <stddef.h>
#include "Effect/CEffect.h"
int main(){printf("m_nQuad=%d QB=%d eKind=%d sizeof=%d\n",(int)offsetof(CEffect,m_nQuad),(int)offsetof(CEffect,m_QuadBuffer),(int)offsetof(CEffect,m_eKind),(int)sizeof(CEffect));return 0;}
