// T05_G02

#include "game.h"

using namespace std;

Game::Game(const string &filename)
{
    ifstream mazeFile(filename);
    string row;
    int rowNumber = 0;

    while (getline(mazeFile, row))
    {
        if (rowNumber < 1)
        {

            // First, we will separate the first line
            // that we find into the two numbers needed
            // to instatiate the maze (the number of rows
            // and the number of cols that it has).

            int separator = row.find('x');
            int numRows = stoi(row.substr(0, separator));
            int numCols = stoi(row.substr(separator + 1));

            // Updating our Game's maze.

            Maze maze(numRows, numCols);
            this->maze = maze;

            rowNumber++;
            continue;
            
        }
        
        for(int colNumber = 0; colNumber < row.length(); colNumber++)
        {
            if(row[colNumber] == '*' || row[colNumber] == '+')
            {

                // The board representation of our maze
                // starts on the second line of the opened file.
                // With that in mind, we instatiate the row of our
                // objects while subtracting '1' from it.

                Post post({rowNumber - 1, colNumber}, row[colNumber]);
                maze.addPost(post);
            }

            else if(row[colNumber] == 'R' || row[colNumber] == 'r')
            {
                Robot robot({rowNumber - 1, colNumber});
                robots.push_back(robot);
            }

            else if(row[colNumber] == 'H' || row[colNumber] == 'h')
            {
                Player player({rowNumber - 1, colNumber});
                this->player = player;
            }
            else if(row[colNumber] == 'O')
            {
                Gate gate ({rowNumber - 1, colNumber});
                maze.addGate(gate);
            }
        }

        rowNumber++;
    }

    mazeFile.close();

}

/******************************************************************************/

bool Game::validMove(char direction)
{
    vector<Post> Posts = maze.getPosts();
    Movement playerMove;
    map<char, Movement> keyToMove;

    // Mapping the different keys to Movement structs
    // that represent the directions to which the user
    // wishes to move.

    keyToMove['Q'] = {-1, -1};
    keyToMove['W'] = {-1, 0};
    keyToMove['E'] = {-1, 1};
    keyToMove['A'] = {0, -1};
    keyToMove['S'] = {0, 0};
    keyToMove['D'] = {0, 1};
    keyToMove['Z'] = {1, -1};
    keyToMove['X'] = {1, 0};
    keyToMove['C'] = {1, 1};

    if(keyToMove.find(direction) == keyToMove.end())

        // In case the key that the user pressed
        // is not found in our map, the iterator map::end
        // is returned, meaning that the char selected
        // is not valid.

        return false;

    playerMove = keyToMove[direction];

    // Retrieve human's coordinates.

    Position playerPos = player.getPosition();

    for (size_t i = 0; i < robots.size(); i++)
    {
        Position robotPos = robots[i].getPosition();

        if (robotPos.col == (playerPos.col + playerMove.dCol) && robotPos.row == (playerPos.row + playerMove.dRow))
        {
            char robotSymbol = robots[i].getSymbol();
            if (robotSymbol == 'r')
                return false;
            if (robotSymbol == 'R')
            {
                player.move(playerMove);
                player.setAsDead();
                return true;
            }
        }
    }

    for (size_t i = 0; i < Posts.size(); i++)
    {

        Position postPos = Posts[i].getPosition();

        if (postPos.col == (playerPos.col + playerMove.dCol) && postPos.row == (playerPos.row + playerMove.dRow))
        {
            char postType = Posts[i].getSymbol();
            if (postType == '+')
                return false;

            if (postType == '*')
            {
                player.setAsDead();
                return true;
            }
        }
    }

    player.move(playerMove);
    return true;

}

/******************************************************************************/

bool Game::play()
{
    vector<Post> Posts = maze.getPosts();
    vector<Gate> Gates = maze.getGates();
    map<int, Position> idToPosition;

    while (player.isAlive()){

        showGameDisplay();
        cout << "\nPick a direction: ";
        char direction = toupper(getChar());

        if(direction == 0)
            return false;
            
        else if(direction == 1)
        {
            cout << "Invalid direction! Please pick a new one." << endl;
            continue;
        }

        if(!validMove(direction))
        {
            cout << "Can't go there! Avoid that obstacle!";
            continue;
        }

        Position playerPos = player.getPosition();

        for (size_t i = 0; i < robots.size(); i++){
            
            if (robots[i].getSymbol() == 'R')

            // In case our robot has been destroyed,
            // do not move it. It must remain stuck
            // until the end of the game. Only move
            // robots that are alive.

            {
                Position beforeRobotPos = robots[i].getPosition();
                robots[i].seekHuman(playerPos);
                
                for (size_t j = 0; j < Posts.size(); j++)
                {

                    // Check each robot and see if it has
                    // collided with an electrified fence
                    // after moving it. Destroy it and move
                    // it back to its original place in case
                    // that happened.

                    char postSymbol = Posts[j].getSymbol();
                    
                    if (collide(robots[i], Posts[j]))
                    {
                        robots[i].setAsDead();
                        if (Posts[j].getSymbol() == '*')
                        {
                            // In case any robot moved to an
                            // electrified post's position, declare
                            // him dead on the spot it was before.

                            robots[i].setPosition(beforeRobotPos);
                        }
                    }

                }

                for (size_t j = 0; j < Gates.size(); j++)
                {

                    // Apply that same logic to the exit gates,
                    // where if a robot moves towards them and
                    // actually collide with any of them, then
                    // it must be destroyed and put back in his
                    // original place.

                    Position gatePos = Gates[j].getPosition();
                    Position robotPos = robots[i].getPosition();

                    if (robotPos.row == gatePos.row && robotPos.col == gatePos.col)
                    {
                        robots[i].setPosition(beforeRobotPos);
                        robots[i].setAsDead();
                    }
                    
                }

                for (size_t j = 0; j < robots.size(); j++)
                {
                    if (i != j)

                        // We can't call the collide function
                        // on the same instance of a robot.

                        if (collide(robots[i], robots[j]))
                        {
                            robots[i].setAsDead();
                            robots[j].setAsDead();
                        }
                }

                // Check each robot and see if it has
                // collided with the player after moving it.
                // Declared him dead in case that happens.

                if (collide(robots[i], player))
                {
                    player.setAsDead();
                    showGameDisplay();
                    return false;
                }

            }

        }

        if (collide(player, Posts)){
                player.setAsDead();
                showGameDisplay();
                return false;
        }

        if (reachedGate()){

            // The game must end if the player
            // reaches one of the maze's exit gates.
            
            return true;
        }
    }
    
    showGameDisplay();
    return false;
}

/******************************************************************************/

bool Game::reachedGate()
{
    vector<Gate> Gates = maze.getGates();
    Position playerPos = player.getPosition();

    for (size_t i = 0; i < Gates.size(); i++)
    {
        Position gatePos = Gates[i].getPosition();
        if (gatePos.row == playerPos.row && gatePos.col == playerPos.col)
            return true;
    }

    return false;
}

/******************************************************************************/

void Game::showGameDisplay() const
{
    int numCols = maze.getnumCols();
    int numRows = maze.getnumRows();
    int numElements = numCols * numRows;

    char board[numRows][numCols];

    for (size_t i = 0; i < numRows; i++)
    {

        // Fill every row of the maze
        // with blank spaces that will
        // eventually be occupied by the
        // objects of the maze.
        
        fill_n(board[i], numCols, ' '); 
    }

    vector<Post> Posts = maze.getPosts();
    vector<Gate> Gates = maze.getGates();   

    for (size_t i = 0; i < Posts.size(); i++)
    {
        Position postPos = Posts[i].getPosition();
        char postSymbol = Posts[i].getSymbol();

        // Putting the posts in their
        // respective places.

        board[postPos.row][postPos.col] = postSymbol;

    }

    for (size_t i = 0; i < robots.size(); i++)
    {
        Position robotPos = robots[i].getPosition();
        char robotSymbol = robots[i].getSymbol();

        // Putting the robots in their
        // respective places.

        board[robotPos.row][robotPos.col] = robotSymbol;

    }

    Position playerPos = player.getPosition();
    char playerSymbol = player.getSymbol();

    // Spawning the human in his current position.

    board[playerPos.row][playerPos.col] = playerSymbol;

    for (size_t i = 0; i < Gates.size(); i++)
    {
        Position gatePos = Gates[i].getPosition();

        // Displaying the maze's exit gates.

        board[gatePos.row][gatePos.col] = 'O';

    }

    cout << "\nTHE MAZE\n";
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)

            // Printing the board elements
            // to the console one by one.

            cout << board[row][col];

        cout << "\n";
    }

}

/******************************************************************************/

bool Game::collide(Robot &robot, Post& post)
{
    Position robotPos = robot.getPosition();
    Position postPos = post.getPosition();

    if (robotPos.row == postPos.row && robotPos.col == postPos.col)
    {
        return true;
    }

    return false;

}

/******************************************************************************/

bool Game::collide(Player &player, vector<Post>& Posts)
{
    for (int i = 0; i < Posts.size(); i++){
        Position playerPos = player.getPosition();
        Position postPos = Posts[i].getPosition();

        if (playerPos.row == postPos.row && playerPos.col == postPos.col)
        {
            return true;
        }
    }
    
    return false;

}

/******************************************************************************/

bool Game::collide(Robot &robot, Player& player)
{
    Position playerPos = player.getPosition();
    Position robotPos = robot.getPosition();

    if (playerPos.row == robotPos.row && playerPos.col == robotPos.col)
    {
            return true;
    }
    
    return false;

}

/******************************************************************************/

bool Game::collide(Robot &firstRobot, Robot &secondRobot)
{
    Position firstRobotPos = firstRobot.getPosition();
    Position secondRobotPos = secondRobot.getPosition();

    if (firstRobotPos.row == secondRobotPos.row && firstRobotPos.col == secondRobotPos.col)
    {
        return true;
    }

    return false;

}
