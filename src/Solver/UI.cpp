#include <iostream>
#include "Experiments.hpp"
#include "UI.hpp"

#ifdef _WIN32
	#include <conio.h>
#else
	#include <curses.h>
#endif

using namespace std;


//____________________________________________________USER INTERFACE_______________________________________________________
void UserInterface::DisplayMenu()
{
    string menuStr = GREETINGS_MSG + menu[currentIndex] + HINT_MSG;
    handler.ResetCursor();
    handler.Print(menuStr);
}

void UserInterface::GoUp()
{
    currentIndex = (currentIndex + numberOfOptions - 1) % numberOfOptions;
    DisplayMenu();
}

void UserInterface::GoDown()
{
    currentIndex = (currentIndex + 1) % numberOfOptions;
    DisplayMenu();
}

UserInterface::UserInterface(vector<string> myOptions)
{
    currentIndex = 0;
    for (int i = 0; i < myOptions.size(); i++)
    {
        string optionsStr = "";
        for (int j = 0; j < myOptions.size(); j++)
        {
            optionsStr += i == j ? CURSOR_STR : NO_CURSOR_STR;
            optionsStr += myOptions[j] + "\n";
        }
        menu.push_back(optionsStr);
    }
    numberOfOptions = menu.size();
}

void UserInterface::Live()
{
    vector<char> kernelTestTypes = { 'W', 'M' };
    vector<string> kernelTestVariants = { "a", "b", "c" };

    handler.ClearWindow();
    DisplayMenu();

    int input = handler.GetUserInput();
    while (input != KEY_ESC)
    {
        switch(input)
        {
            case KEY_UP:
                GoUp();
                input = handler.GetUserInput();
                break;

            case KEY_DOWN:
                GoDown();
                input = handler.GetUserInput();
                break;
            
            case KEY_ENT:
                //handler.ClearWindow();
                handler.EndWindow();
                switch(currentIndex)
                {
                    case 0: case 1: case 2:
                        run.Experiment_14_4(currentIndex);
                        break;
                
                    case 3:
                        run.Experiment_14_6('W', "Competition radius");
                        break;
                
                    case 4:
                        run.Experiment_14_6('M', "Dispersal radius");
                        break;
                
                    case 5:
                        handler.Print(CUSTOM_HINT_MSG);
                        input = handler.GetUserInput();
                        while (input != KEY_ENT && input != KEY_ESC)
                        {
                            input = handler.GetUserInput();
                        }
                        if (input == KEY_ENT)
                        {
                            handler.EndWindow();
                            run.Custom_Experiment();
                        }
                        break;

                    case 6:
                        for (auto& kernelType : kernelTestTypes)
                        {
                            for (auto& variant : kernelTestVariants)
                            {
                                run.KernelTest(kernelType, variant);
                                cout << "Press any key to continue.\n";
                                handler.GetUserInput(false);
                            }
                        }
                        break;

                    default:
                        handler.Print("ERROR: Experiment does not exist!\n");
                        break;
                }
                cout << "Press any key to finish.\n";
                handler.GetUserInput(false);
                cout.flush();

                // Reset input
                input = -1;

                handler.ClearWindow();
                DisplayMenu();
                break;
            
            default:
                input = handler.GetUserInput();
                break;
        }
    }
    handler.ClearWindow();
}
