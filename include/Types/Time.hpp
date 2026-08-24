#pragma once 

#include <iosfwd>
#include <string>


//________________________________________________TIME FROM CLOCK_T_________________________________________________
class Time
{
    std::string strSeconds;
    std::string strMinutes;
    std::string strHours;

public:
    Time(clock_t time);

    //....................Display time
    //....................Format:
    //....................   hh:mm:ss
    friend std::ostream& operator << (std::ostream& out, const Time &t);
};