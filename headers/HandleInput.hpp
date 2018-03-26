#ifndef _HANDLE_INPUT_
#define _HANDLE_INPUT_

#include "miniwin.h"
using namespace miniwin;

class HandleInput
{
    static int key;

    public:
    HandleInput(){}

    static void updateKey()
    {
        HandleInput:: key = tecla();
    }
    
    static int getKey()
    {
        return HandleInput:: key;
    }
};

int HandleInput :: key = 0;

#endif