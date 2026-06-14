#pragma once
// Auto-generated: DIDEVICEOBJECTINSTANCEA

class DIDEVICEOBJECTINSTANCEA {
public:
    UINT dwSize; // +0x0
    _GUID guidType; // +0x4
    char _gap_008[12]; // +0x8
    UINT dwOfs; // +0x14
    UINT dwType; // +0x18
    UINT dwFlags; // +0x1C
    char tszName[324]; // +0x20
    UINT dwFFMaxForce; // +0x164
    UINT dwFFForceResolution; // +0x168
    WORD wCollectionNumber; // +0x16C
    WORD wDesignatorIndex; // +0x16E
    WORD wUsagePage; // +0x170
    WORD wUsage; // +0x172
    UINT dwDimension; // +0x174
    WORD wExponent; // +0x178
    WORD wReportId; // +0x17A
    // total size: 0x17C (380)

};
