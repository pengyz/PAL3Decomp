#pragma once
// Auto-generated: _Item

class _Item {
public:
    char title[16]; // +0x0 (std::basic_string<char,std::char_traits<char>,std::allocator<char> >)
    char info[16]; // +0x10 (std::basic_string<char,std::char_traits<char>,std::allocator<char> >)
    unsigned char bHasChild; // +0x20
    int nChildNum; // +0x24
    unsigned char bIsPic; // +0x28
    _Item * * ppChildren; // +0x2C
    // total size: 0x30 (48)

};
