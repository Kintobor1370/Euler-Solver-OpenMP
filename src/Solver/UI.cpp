#include <iostream>
#include <conio.h>
#include "Experiments.hpp"
#include "UI.hpp"

using namespace std;


//____________________________________________________USER INTERFACE_______________________________________________________
void UserInterface::DisplayMenu()
{
    system("cls");
    cout << GREETINGS_MSG + menu[currentIndex] + HINT_MSG;   
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
            optionsStr += i == j ? CHOSEN_STR : EMPTY_STR;
            optionsStr += myOptions[j] + "\n";
        }
        menu.push_back(optionsStr);
    }
    numberOfOptions = menu.size();
}

void UserInterface::Live()
{
    DisplayMenu();
    char input = getch();

    while(input != KEY_ESC)
    {
        switch (input)
        {
            case KEY_UP:
                GoUp();
                input = getch();
                break;

            case KEY_DOWN:
                GoDown();
                input = getch();
                break;

            case KEY_ENT:
                system("cls");
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
                        cout << CUSTOM_HINT_MSG;
                        input = getch();
                        if (input == KEY_ENT)
                        {
                            system("cls");
                            run.Custom_Experiment();
                        }
                        else if (input != KEY_ESC)
                            input = getch();
                        break;

                    case 6:
                        run.KernelTest('W', "a");
                        cout << "Press any key\n";
                        getch();
                        run.KernelTest('W', "b");
                        cout << "Press any key\n";
                        getch();
                        run.KernelTest('W', "c");
                        cout << "Press any key\n";
                        getch();
                        run.KernelTest('M', "a");
                        cout << "Press any key\n";
                        getch();
                        run.KernelTest('M', "b");
                        cout << "Press any key\n";
                        getch();
                        run.KernelTest('M', "c");
                        cout << "Tests Complete!\n";
                        break;

                    default:
                        cout << "ERROR: No such experiment!!\n";
                        break;
                }

            default:
                input = getch();
                break;
        }
    }
    system("cls");
}