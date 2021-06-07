// T05_G02

#include <time.h>

#include "movement.h"
#include "menu.h"
#include "game.h"
#include "high_score.h"

using namespace std;

int main()
{   
    string filename;
    Menu menu;
    if(menu.menuLoop())
        return 0;

    filename =  menu.selectMaze();
    if(filename == "")
        return 0;

    Game game(filename);
    time_t startTime = time(0);
    if(game.play())
    {
        cout << "You won!" << endl;
        int secondsToWin = lround(difftime(time(0), startTime));
        highScores highscores;
        highscores.handle(filename.substr(0, 7) + "_WINNERS.TXT", secondsToWin);
    }
    else
        cout << "You lost!" << endl;

    return 0;
}