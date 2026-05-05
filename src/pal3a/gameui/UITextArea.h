#ifndef PAL3A_UITEXTAREA_H
#define PAL3A_UITEXTAREA_H

#include "pal3a_types.h"

class UITextArea {
public:
    char _data[104];

    void Clear();
    void NextPage();
    bool IfEmpty();
    void AddText(char * str);
    int Draw(std::basic_string<char,std::char_traits<char>,std::allocator<char> > * text, int * flag);
    ~UITextArea();
    int BuildDrawHeight(std::basic_string<char,std::char_traits<char>,std::allocator<char> > * text);
    UITextArea();
    void Render();
};

#endif // PAL3A_UITEXTAREA_H
