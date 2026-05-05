#ifndef PAL3A_UIDIALOG_H
#define PAL3A_UIDIALOG_H

#include "pal3a_types.h"

class UIDialog {
public:
    char _data[72];

    int Update(float deltatime, int haveinput);
    ~UIDialog();
    UIDialog();
};

#endif // PAL3A_UIDIALOG_H
