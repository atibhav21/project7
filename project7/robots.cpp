//
//  main.cpp
//  project7
//
//  Created by Atibhav Mittal on 11/28/15.
//  Copyright © 2015 ati. All rights reserved.
//

// robots.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the arena
const int MAXCOLS = 30;             // max number of columns in the arena
const int MAXROBOTS = 100;          // max number of robots allowed

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Robot declaration.

class Robot
{
public:
    // Constructor
    Robot(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool getAttacked(int dir);
    
    
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    timesHit;
    // You'll probably find that a robot object needs an additional
    // data member to support your implementation of the behavior affected
    // by being hit and taking damage.
};

class Player
{
public:
    // Constructor
    Player(Arena *ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    void   stand();
    void   moveOrAttack(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;
};

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;
    
    // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    bool   attackRobotAt(int r, int c, int dir);
    bool   moveRobots();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    int     m_nRobots;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////

Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    timesHit = 0;
}

int Robot::row() const
{
    // Return what row the robot is at.
    return m_row;
}

int Robot::col() const
{
    // Return what column the robot is at.
    return m_col;  // This implementation compiles, but is incorrect.
}

void Robot::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    int dir = randInt(0, 3);  // dir is now UP, DOWN, LEFT, or RIGHT
    
    m_arena->determineNewPosition(m_row, m_col, dir);
    
    // Attempt to move in direction dir; if we can't move, don't move.
}

bool Robot::getAttacked(int dir)  // return true if dies
{
    // If the robot has been attacked once before, return true
    // (since a second attack kills a robot).  Otherwise, if possible, move
    // the robot in one position in direction dir and return false (since
    // it survived the damage).  Otherwise, do not move, but return true
    // (since the momentum from the blow would bump the robot against the
    // wall, dealing it additional fatal damage).
    if(timesHit==1)
    {
        timesHit++;
        return true;
    }
    else if(timesHit == 0)
    {
        timesHit++;
        if(dir == UP)
        {
            if(row() > 1)
            {
                m_row--;
            }
            else
            {
                timesHit++;
                return true;
            }
        }
        else if(dir == DOWN)
        {
            if(row() < m_arena->rows())
            {
                m_row++;
            }
            else
            {
                timesHit++;
                return true;
            }
        }
        else if(dir == LEFT)
        {
            if(col()> 1)
            {
                m_col--;
            }
            else
            {
                timesHit++;
                return true;
            }
        }
        else if(dir == RIGHT)
        {
            if(col()< m_arena->cols())
            {
                m_col++;
            }
            else{
                timesHit++;
                return true;
            }
        }
    }
    
    
    return false;
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    // Return what row the player is at.
    // Delete the following line and replace it with the correct code.
    return m_row;  // This implementation compiles, but is incorrect.
}

int Player::col() const
{
    // Return what column the player is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // This implementation compiles, but is incorrect.
}

int Player::age() const
{
    // Return the player's age.
    // Delete the following line and replace it with the correct code.
    return m_age;  // This implementation compiles, but is incorrect.
}

void Player::stand()
{
    m_age++;
}

void Player::moveOrAttack(int dir)
{
    m_age++;
    if(dir == UP && m_row > 1)
    {
        if(m_arena->nRobotsAt(m_row-1, m_col)>0)
        {
            m_arena->attackRobotAt(m_row - 1, m_col, dir);
        }
        else
        {
            m_arena->determineNewPosition(m_row, m_col, dir);
        }
    }
    else if(dir == DOWN && m_row < m_arena->rows())
    {
        if(m_arena->nRobotsAt(m_row + 1, m_col)> 0)
        {
            m_arena->attackRobotAt(m_row+1, m_col, dir);
        }
        else
        {
            m_arena->determineNewPosition(m_row, m_col, dir);
        }
    }
    else if(dir == LEFT && m_col > 1)
    {
        if(m_arena->nRobotsAt(m_row, m_col-1)> 0)
        {
            m_arena->attackRobotAt(m_row, m_col-1, dir);
        }
        else
        {
            m_arena->determineNewPosition(m_row, m_col, dir);
        }
    }
    else if(dir == RIGHT && m_col < m_arena->cols())
    {
        if(m_arena->nRobotsAt(m_row, m_col+1)> 0)
        {
            m_arena->attackRobotAt(m_row, m_col+1, dir);
        }
        else
        {
            m_arena->determineNewPosition(m_row, m_col, dir);
        }
    }
    // If there is a robot adjacent to the player in the direction
    // dir, attack it.  Otherwise, move the player to that position if
    // possible (i.e., if the move would not be off the edge of the arena).
}

bool Player::isDead() const
{
    // Return whether the player is dead.
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementations
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRobots = 0;
}

Arena::~Arena()
{
    // Delete the player and all remaining dynamically allocated robots.
    delete m_player;
    for(int i = 0; i<m_nRobots; i++)
    {
            delete m_robots[i];
    }
}

int Arena::rows() const
{
    // Return the number of rows in the arena.
    return m_rows;
}

int Arena::cols() const
{
    // Return the number of columns in the arena.
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    // Return the number of robots in the arena
    return m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const
{
    // Return the number of robots at row r, column c.
    if(r<1 || r>m_rows || c<1 || c>m_cols)
    {
        return -1;
    }
    int count = 0;
    for(int i = 0; i<m_nRobots; i++)
    {
        if(m_robots[i]!= nullptr && m_robots[i]->row() == r && m_robots[i]->col() == c)
        {
            count++;
        }
    }
    return count;
}

bool Arena::determineNewPosition(int& r, int& c, int dir) const
{
    // If a move from row r, column c, one step in direction dir
    // would go off the edge of the arena, leave r and c unchanged and
    // return false.  Otherwise, set r or c so that row r, column c, is
    // now the new position resulting from the proposed move, and
    // return true.
    if(r<1 || r>m_rows || c<1 || c>m_cols)
    {
        return false;
    }
    switch (dir)
    {
        case UP:
            // Implement the behavior if dir is UP.
            if(r>1)
            {
                r--;
            }
            else
            {
                return false;
            }
            break;
        case DOWN:
            if(r< m_rows)
            {
                r++;
            }
            else
            {
                return false;
            }
            break;
        case LEFT:
            if(c>1)
            {
                c--;
            }
            else
            {
                return false;
            }
            break;
        case RIGHT:
            if(c< m_cols)
            {
                c++;
            }
            else
            {
                return false;
            }
            // Implement the other directions.
            break;
        default:
            return false;
    }
    return true;
}

void Arena::display() const
{
    // Position (row,col) in the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    //        Indicate each robot's position
    //        If one robot is at some grid point, set the char to 'R'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    for(r = 0; r< rows();r++)
    {
        for(c = 0; c< cols();c++)
        {
            int count = nRobotsAt(r+1, c+1);
            if(count == 1)
            {
                grid[r][c] = 'R';
            }
            else if(count>=2 && count<= 8)
            {
                grid[r][c] = (char)(count + '0');
            }
            else if(count>=9)
            {
                grid[r][c] = '9';
            }
            else if(count == -1)
            {
                
            }
            
        }
    }
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a robot there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    
    // Write message, robot, and player info
    cout << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addRobot(int r, int c)
{
    // If MAXROBOTS have already been added, return false.  Otherwise,
    // dynamically allocate a new robot at coordinates (r,c).  Save the
    // pointer to the newly allocated robot and return true.
    
    // Implement this.
    if(r<1 || r>m_rows || c<1 || c>m_cols)
    {
        return false;
    }
    if(m_nRobots == MAXROBOTS)
    {
        return false;
    }
    
    else
    {
        Robot* rob = new Robot(this, r, c);
        m_robots[m_nRobots] = rob;
        m_nRobots++;
        return true;
    }
    
}

bool Arena::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    if(r<1 || r>m_rows || c<1 || c>m_cols)
    {
        return false;
    }
    
    // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
}

bool Arena::attackRobotAt(int r, int c, int dir)
{
    // Attack one robot at row r, column c if at least one is at
    // that position.  If the robot does not survive the damage, destroy the
    // robot object, removing it from the arena, and return true.  Otherwise,
    // return false (no robot at (r,c), or robot didn't die).
    if(r<1 || r>m_rows || c<1 || c>m_cols)
    {
        return false;
    }
    if(nRobotsAt(r, c) == 0)
    {
        return false;
    }
    else
    {
        bool moveMade = false;
        for(int i = 0; i<m_nRobots && !moveMade ; i++) //not found a robot yet at that position
        {
            if(m_robots[i]!= nullptr && m_robots[i]->row()== r && m_robots[i]->col()== c)
            {
                moveMade = true;
                bool isDead = m_robots[i]->getAttacked(dir);
                if(isDead == true)
                {
                    delete m_robots[i];
                    //m_robots[i] = nullptr;
                    for(int j = i; j<m_nRobots - 1; j++)
                    {
                        m_robots[j] = m_robots[j+1];
                    }
                    m_nRobots--;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Arena::moveRobots()
{
    for (int k = 0; k < m_nRobots; k++)
    {
        //        Have the k-th robot in the arena make one move.
        //        If that move results in that robot being in the same
        //        position as the player, the player dies.
        if(m_robots[k]!= nullptr) //robot has been destroyed
        {
            m_robots[k]->move();
            if(m_robots[k]->row() == m_player->row() && m_robots[k]->col() == m_player->col())
            {
                m_player->setDead();
            }
        }
    }
    
    // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}


///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRobots)
{
    if (nRobots < 0)
    {
        cout << "***** Cannot create Game with negative number of robots!" << endl;
        exit(1);
    }
    if (nRobots > MAXROBOTS)
    {
        cout << "***** Trying to create Game with " << nRobots
        << " robots; only " << MAXROBOTS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nRobots > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the robots!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with robots
    while (nRobots > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a robot where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_arena->addRobot(r, c);
        nRobots--;
    }
}

Game::~Game()
{
    delete m_arena;
}

void Game::play()
{
    Player* p = m_arena->player();
    if (p == nullptr)
    {
        m_arena->display();
        return;
    }
    do
    {
        m_arena->display();
        cout << endl;
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)  // player stands
            p->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->moveOrAttack(decodeDirection(action[0]));
                    break;
            }
        }
        m_arena->moveRobots();
    } while ( ! m_arena->player()->isDead()  &&  m_arena->robotCount() > 0);
    m_arena->display();
}



///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}



///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    //Game g(3, 4, 2);
    
    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
