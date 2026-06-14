#include "AStarPathFinder.h"
#pragma once
// Auto-generated: PathFinder

class NavTileLayer;
class Role;

class PathFinder : public AStarPathFinder {
public:
    char _gap_000[24]; // +0x0
    NavTileLayer * m_curlayer; // +0x18
    int m_layer; // +0x1C
    Role * m_pRole; // +0x20
    // total size: 0x24 (36)

};
