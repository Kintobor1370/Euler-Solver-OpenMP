#include <iostream>
#include "Time.hpp"

using namespace std;


//________________________________________________TIME FROM CLOCK_T_________________________________________________
Time::Time(clock_t time)
{
    int seconds = (int) time / CLOCKS_PER_SEC;
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;

    strSeconds = seconds / 10 == 0 ? "0" + to_string(abs(seconds)) : to_string(abs(seconds));
    strMinutes = minutes / 10 == 0 ? "0" + to_string(abs(minutes)) : to_string(abs(minutes));
    strHours = to_string(abs(hours));
}

ostream& operator << (ostream& out, const Time &t)
{
    out << t.strHours << ':' << t.strMinutes << ':' << t.strSeconds;
    return out;
}