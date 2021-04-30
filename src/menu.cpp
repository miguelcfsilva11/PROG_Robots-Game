// T05_G02

#include <iostream>
#include <iomanip>
#include <ios>
#include <limits>

using namespace std;

int menu();

/******************************************************************************/

/**
* Clears the screen by outputting 100 new lines.
*/
void clearScreen()
{
    for(short i = 0; i < 10; i++)
    {
        cout << "\n\n\n\n\n\n\n\n\n\n";
    }
}

/******************************************************************************/

/**
* Displays the rules of the game.
*/
void displayRules()
{
    clearScreen();
    cout << "Welcome to the Rules section!" << endl
         << "(Hit ENTER to go back to the menu)\n" << endl
         << "-> When you select the option to play the game in the menu screen you will be prompted to choose wich level you want to play." << endl
         << "-> After choosing the level, you will be placed in a maze made up of high-voltage fences and posts." << endl
         << "-> There will also be some interceptor robots that will try to destroy you, be careful!" << endl
         << "-> If at any moment you touch the high-voltage fences and posts or the robots you lose the game." << endl
         << "-> Every time you move, each robot will also move one cell closer to you." << endl 
         << "-> To win the game, you must make the robots colide with each other or the maze in other to destroy them." << endl 
         << "-> In order to move you have to type Q, W, E, A, S, D, Z, X, or C." << endl;

    getchar();
}

/******************************************************************************/

/**
* Displays the menu screen and prompts the user to choose one of the options.
* 
* @return 0 when the user chooses to exit.
* @return 1 when the menu needs to be displayed again.
* @return 2 when the user chooses to play the game.
*/

int menu()
{
    clearScreen();
    
    int userChoice; // Stores an integer representing the menu option that the user chose.

    cout << "Welcome to Robots Game! Please select one of the options below.\n" << endl
         << "0) Exit." << endl
         << "1) Rules." << endl
         << "2) Play." << endl;

    cin >> userChoice;

    // Checking for and dealing with invalid input.
    if(cin.fail())
    {
        if(cin.eof())
            return 0;
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return 1;
        }
    }
    else 
    {
        if(cin.peek() != '\n')
            {
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                return 1;
            }
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    // Reacting to valid user input.
    switch(userChoice)
    {
        case 0:
            // Exit.
            return 0;
        case 1:
            // Display the Rules.
            displayRules();
            return 1;
        case 2:
            // Start the Game.
            return 2;
        default:
            // Back to Menu.
            return 1;
    }
}