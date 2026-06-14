#pragma once
// Auto-generated: ArcPastScene

class ArcPastScene {
public:
    char cityname[32]; // +0x0
    char name[32]; // +0x20
    // total size: 0x40 (64)

    bool LoadCityData(); // 0x00533B50
    int ResetCityName(); // 0x00534F50
    void FreeChildList(); // 0x00534FB0
};
