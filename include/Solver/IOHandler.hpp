#pragma once

#ifndef _WIN32
	#include <curses.h>
#endif

class IOHandler
{
    #ifndef _WIN32
        WINDOW *win;
        int defaultHeight;
        int defaultWidth;
        int initX;
        int initY;
    #endif

public:
    IOHandler();

    ~IOHandler();

    int GetUserInput(bool isWindow = true);

    void Print(std::string str);

    void ClearWindow();
    
    void ResetCursor();

    void EndWindow();
};