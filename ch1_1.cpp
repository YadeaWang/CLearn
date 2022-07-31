#include <iostream>
bool isLeapYear(int);

int main() 
{
    int year = -1;
    while(true)
    {
        std::cout << "Please input a year number: " << std::endl;
        std::cin >> year;
        if(year == 0)
            break;
        if(isLeapYear(year))
            std::cout << "The total days are: 366" << std::endl;
        else
            std::cout << "The total days are: 365" << std::endl;
    }
}

bool isLeapYear(int year)
{
    if((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
    {
        return true;
    }
    return false;
}