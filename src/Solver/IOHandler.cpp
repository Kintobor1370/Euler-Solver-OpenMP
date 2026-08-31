#include <iostream>
#include "IOHandler.hpp"
#ifdef _WIN32
	#include <conio.h>
#else
    #include <termios.h>
	#include <unistd.h>
#endif

using namespace std;


IOHandler::IOHandler()
{
    #ifndef _WIN32
        defaultHeight = 100;
        defaultWidth = 100;
        initX = 0;
        initY = 0;
        
        system("clear");
        initscr();
        noecho();
        cbreak();

        win = newwin(defaultHeight, defaultWidth, initX, initY);

        keypad(win, true);
        scrollok(win, true);
        //idlok(win, true);
    #endif
}

IOHandler::~IOHandler()
{
    #ifndef _WIN32
        delwin(win);
        endwin();
    #endif
}

int IOHandler::GetUserInput(bool isWindow)
{
    #ifdef _WIN32
        return getch();
    #else
        if (isWindow)
        {
            return wgetch(win);
        }
        int input;
        termios oldSettings{};
      	tcgetattr(STDIN_FILENO, &oldSettings);
      
      	termios newSettings = oldSettings;
      	newSettings.c_lflag &= ~(ICANON | ECHO);
      
      	tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
      	read(STDIN_FILENO, &input, 1);
      	tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);

        return input;
    #endif
}

void IOHandler::Print(string str)
{
    #ifdef _WIN32
        cout << str;
    #else
        wprintw(win, str.c_str());
        wrefresh(win);
    #endif
}

void IOHandler::ClearWindow()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
        wclear(win);
        wrefresh(win);
    #endif
}

void IOHandler::ResetCursor()
{
    #ifdef _WIN32
        system("cls");
    #else
        move(initX, initY);
        mvwprintw(win, initX, initY, "");
    #endif
}

void IOHandler::EndWindow()
{
    #ifdef _WIN32
        system("cls");
    #else
        endwin();
    #endif
}

