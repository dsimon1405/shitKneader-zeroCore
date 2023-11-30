#pragma once

#include <ZC/Tools/Signal/ZC_Signals.h>
#include "ZC_Keys.h"

struct ZC_Button
{
    enum State
    {
        Pressed,
        Unpressed
    };

    ZC_Keys key;
    State state;

    bool operator 
};

class ZC_Keyboard
{
public:
    ZC_Keyboard() = delete;
    
    void Assume

private:

};