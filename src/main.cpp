/**************************************************************************************************************************
**                                                        MAIN BODY                                                      **
**************************************************************************************************************************/
#include <vector>
#include <string>
#include "UI.hpp"

int main()
{
    std::vector<std::string> commands {
        "14.4.a",
        "14.4.b",
        "14.4.c",
        "14.6.a",
        "14.6.b",
        "Custom experiment",
        "Kernels Test"
    };

    UserInterface UI(commands);
    UI.Live();
    
    return 0;
}