#include <iostream>
#include <iomanip>
#include <ios>
#include <limits>
#include "menu.h"

using namespace std;

int main()
{
    int menuOption = menu();
    while(menuOption == 1)
        menuOption = menu();

    if(menuOption == 0)
        return 0;


    return 0;
}
