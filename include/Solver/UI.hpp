#pragma once

#include "IOHandler.hpp"
#include "Experiments.hpp"

#ifdef _WIN32
    #define KEY_UP 72
    #define KEY_DOWN 80
    #define KEY_ENT 13
    #define KEY_ESC 27
#else
    #define KEY_ENT 10
    #define KEY_ESC 27
#endif


//____________________________________________________USER INTERFACE_______________________________________________________
class UserInterface
{
    IOHandler handler;
    Experiments run;
    std::vector<std::string> menu;
    int numberOfOptions;
    int currentIndex;
    int cursorX;                            // Cursor location X for Linux output
    int cursorY;                            // Cursor location Y for Linux output
    
private:
    const std::string CURSOR_STR = "  > ";
    const std::string NO_CURSOR_STR = "    ";
    const std::string GREETINGS_MSG = "Welcome!\nPlease choose experiment:\n";
    const std::string HINT_MSG = "\n(Navigate with up arrow & down arrow\n Press ENTER to confirm\n Press ESC to quit)\n";
    const std::string CUSTOM_HINT_MSG = "Please navigate to \'Data\\Custom\' folder and fill the \'experiment.csv\' file according to the example.\nPress ENTER to confirm and start the experiment\nPress ESC to quit\n";

    void InitialiseWindow();
    
    void ClearWindow();

    void DisplayMenu();

    void GoUp();

    void GoDown();

public:
    UserInterface(std::vector<std::string> myOptions);

    void Live();
};
