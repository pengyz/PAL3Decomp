#pragma once
// Auto-generated: AStarPathFinder

class AStarPathFinder {
public:
    char OPEN[4]; // +0x4 (AStarPathFinder::NODE *)
    char CLOSED[4]; // +0x8 (AStarPathFinder::NODE *)
    char PATH[4]; // +0xC (AStarPathFinder::NODE *)
    char Stack[4]; // +0x10 (AStarPathFinder::STACK *)
    int m_TestTimer; // +0x14
    // total size: 0x18 (24)

};
