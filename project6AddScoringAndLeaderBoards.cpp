#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <conio.h> //Contains functions for non-buffered console input (_getch() on Windows)
#include <limits> // For numeric_limits
#include <chrono> // For timer
#include <thread> // For sleep
#include <algorithm>

#define GRID_SIZE 9
using namespace std;

// Initialize Ansi Colors
const string ANSI_RESET = "\033[0m";
const string ANSI_RED = "\033[1;31m";
const string ANSI_YELLOW = "\033[1;33m";
const string ANSI_PURPLE = "\033[1;35m";
const string ANSI_ORANGE = "\033[38;5;208m";
const string ANSI_GREEN = "\033[1;32m";
const string ANSI_D_BLUE = "\033[38;5;23m";
const string ANSI_FLAME = "\033[38;5;202m";

// Structure to represent a player's data
struct Player {
    string username;
    int score;
};
const int MAX_PLAYERS = 10;
Player leaderboard[MAX_PLAYERS];


void exitGame(bool &puzzleSolved)
{
    system("cls");
    cout << "Are you sure you want to exit? Your progress is not saved\n\nEnter Y to Confirm, Enter Any Other Key to Cancel " << endl;
    char confirmation;
    cin >> confirmation;
    if (confirmation == 'y' || confirmation == 'Y')
    {
        puzzleSolved = true;
        cout << ANSI_FLAME <<"\n See You next time, friend!" << ANSI_RESET;
    }
    else
    {
        puzzleSolved = false;
    }
}
 
void printScore(int elapsedSeconds, int numToDelete, int& userScore) {
    if (numToDelete == 2) {
     
        userScore = numToDelete * 50 * elapsedSeconds;
    } else if (numToDelete == 54) {
    
        userScore = numToDelete * 150 * elapsedSeconds;
    } else if (numToDelete == 63) {
    
        userScore = numToDelete * 200 * elapsedSeconds;
    }
    cout << userScore;
}




bool validateInput(int &number)
{
    cin >> number;
    if (cin.fail() || number < 0 || number > 9)
    {
        // Clear input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between 0 and 9." << endl;
        return false;
    }
    return true;
}

void handleInput(int &number, bool emptyCells[GRID_SIZE][GRID_SIZE], int sudokuGrid[GRID_SIZE][GRID_SIZE], int row, int col)
{

    if (!emptyCells[row][col])
    {
        cout << "This cell contains a fixed number and cannot be modified." << endl;
        _getch();
        return;
    }
    if (sudokuGrid[row][col] == 0)
    {
        cout << ANSI_GREEN << "Enter 0 to leave it empty \n\nEnter the desired number (0-9): " << ANSI_RESET;
        while (!validateInput(number))
        {
            cout << "Enter number (0-9): ";
        }
        sudokuGrid[row][col] = number;
    }
    else
    {
        cout << "Do you want to erase the number? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            sudokuGrid[row][col] = 0; // Erase the number
            emptyCells[row][col] = true; 
            /* regardless of this, it will always be known as an empty cell
            this step is redundant*/ 
        }
    }
}
bool verifySolution(int sudokuGrid[GRID_SIZE][GRID_SIZE], int comparsionGrid[GRID_SIZE][GRID_SIZE])
{

    // must compare comparsionGrid to sodukuGrid
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            if (sudokuGrid[i][j] != comparsionGrid[i][j])
            {
                // If any corresponding elements are different, arrays are not identical
                return false;
            }
        }
    }
    // All corresponding elements are the same, arrays are identical

    return true;
}

void endGame(int sudokuGrid[GRID_SIZE][GRID_SIZE], int comparsionGrid[GRID_SIZE][GRID_SIZE],
             bool allCellsFilled, bool &solutionValidated, bool &puzzleSolved, int elapsedSeconds,
            int &userScore, int numToDelete)
{
    solutionValidated = false;
    allCellsFilled = true;
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            if (sudokuGrid[i][j] == 0)
            {
                allCellsFilled = false;
                break;
            }
        }
        if (!allCellsFilled)
        {

            break;
        }
    }

    if (allCellsFilled)
    {
        // Validate Sudoku solution
        if (verifySolution(sudokuGrid, comparsionGrid))
        {
            cout << ANSI_FLAME << "Congratulations! You have solved the puzzle." << ANSI_RESET << endl;
            solutionValidated = true;
            puzzleSolved = true;
        }
        else
        {

            if (!solutionValidated)
            {
                system("cls");
                cout << ANSI_RED << " Better Luck Next Time XD, SIT YOUR HEART ABLAZE!" << ANSI_RESET;
                puzzleSolved = true;
                solutionValidated = false;
                _getch(); // Wait for user input
                system("cls");
            }
        }
    }
    else
    {
        cout << "\t\t\t\nPlease fill all cells before confirming, press any key to continue" << endl;
        _getch();
    }

    if (numToDelete == 2) {
        userScore = numToDelete * 50 * elapsedSeconds;
    } else if (numToDelete == 54) {
        userScore = numToDelete * 150 * elapsedSeconds;
    } else if (numToDelete == 63) {
        userScore = numToDelete * 200 * elapsedSeconds;
    } 
    // Update player data
    Player currentPlayer; 
    cout << "Please enter your username: ";
    cin >> currentPlayer.username;
    currentPlayer.score = userScore;
    
    // Add current player to the leaderboard
    leaderboard[MAX_PLAYERS - 1] = currentPlayer;
    
    // Sort leaderboard by score
    sort(begin(leaderboard), end(leaderboard), [](const Player &a, const Player &b) {
        return a.score > b.score;
    });

    // Display leaderboard
    system("cls");
    cout << "Leaderboard:" << endl;
    cout << "Position\tName\t\tScore" << endl;
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        cout << i + 1 << "\t\t" << leaderboard[i].username << "\t\t" << leaderboard[i].score << endl;
        if (leaderboard[i].username == currentPlayer.username && leaderboard[i].score == currentPlayer.score) {
            cout << "Your Position: " << i + 1 << "\tYour Score: " << leaderboard[i].score << endl;
        }
    }

    
    

}

void confirmSolution(int sudokuGrid[GRID_SIZE][GRID_SIZE], int comparsionGrid[GRID_SIZE][GRID_SIZE], bool &allCellsFilled, bool &solutionValidated, bool &puzzleSolved, int elapsedSeconds, int &userScore, int numToDelete)
{
    endGame(sudokuGrid, comparsionGrid, allCellsFilled, solutionValidated, puzzleSolved, elapsedSeconds, userScore, numToDelete);

}

// Function to print the Sudoku grid
void printGrid(int grid[GRID_SIZE][GRID_SIZE], int numToDelete, bool localize[GRID_SIZE][GRID_SIZE])
{
    // Delete elements randomly
    srand(time(0));

    for (int k = 0; k < numToDelete; ++k)
    {
        int row = rand() % GRID_SIZE;
        int col = rand() % GRID_SIZE;
        grid[row][col] = 0;        // Set the element to 0 to indicate it's empty
        localize[row][col] = true; // used for color mapping of ansi
    }

    // Print the grid
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            if (grid[i][j] != 0)
            {
                cout << ANSI_D_BLUE << grid[i][j] << " " << ANSI_RESET;
            }
            else
            {
                cout << "  ";
            }
            if ((j + 1) % 3 == 0 && j != GRID_SIZE - 1)
            {
                cout << ANSI_PURPLE << "| " << ANSI_RESET; // Print vertical line after every 3 columns
            }
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i != GRID_SIZE - 1)
        {
            cout << ANSI_PURPLE << "------+-------+------" << ANSI_RESET << endl; // Print horizontal line after every 3 rows
        }
    }
}

void generateUniqueRandomNumbers(int &a, int &b, int &c, int &d, int &e, int &f, int &g, int &h, int &i)
{
    // Generate random numbers for each variable ensuring uniqueness
    a = rand() % 9 + 1;
    b = rand() % 9 + 1;
    while (b == a)
        b = rand() % 9 + 1;
    c = rand() % 9 + 1;
    while (c == a || c == b)
        c = rand() % 9 + 1;
    d = rand() % 9 + 1;
    while (d == a || d == b || d == c)
        d = rand() % 9 + 1;
    e = rand() % 9 + 1;
    while (e == a || e == b || e == c || e == d)
        e = rand() % 9 + 1;
    f = rand() % 9 + 1;
    while (f == a || f == b || f == c || f == d || f == e)
        f = rand() % 9 + 1;
    g = rand() % 9 + 1;
    while (g == a || g == b || g == c || g == d || g == e || g == f)
        g = rand() % 9 + 1;
    h = rand() % 9 + 1;
    while (h == a || h == b || h == c || h == d || h == e || h == f || h == g)
        h = rand() % 9 + 1;
    i = rand() % 9 + 1;
    while (i == a || i == b || i == c || i == d || i == e || i == f || i == g || i == h)
        i = rand() % 9 + 1;
}

void plugElementA(int a, int grid[GRID_SIZE][GRID_SIZE])
{
    grid[0][0] = a;
    grid[1][3] = a;
    grid[2][7] = a;
    grid[3][2] = a;
    grid[4][4] = a;
    grid[5][6] = a;
    grid[6][1] = a;
    grid[7][5] = a;
    grid[8][8] = a;
}

void plugElementB(int b, int grid[GRID_SIZE][GRID_SIZE])
{
    grid[1][2] = b;
    grid[2][5] = b;
    grid[0][7] = b;
    grid[4][0] = b;
    grid[5][4] = b;
    grid[3][6] = b;
    grid[7][1] = b;
    grid[8][3] = b;
    grid[6][8] = b;
}

void plugElementC(int c, int grid[GRID_SIZE][GRID_SIZE])
{
    grid[2][0] = c;
    grid[0][5] = c;
    grid[1][7] = c;
    grid[5][2] = c;
    grid[3][4] = c;
    grid[4][8] = c;
    grid[8][1] = c;
    grid[6][3] = c;
    grid[7][6] = c;
}

void plugElementD(int d, int grid[GRID_SIZE][GRID_SIZE])
{
    grid[0][1] = d;
    grid[2][3] = d;
    grid[1][6] = d;
    grid[3][0] = d;
    grid[5][5] = d;
    grid[4][7] = d;
    grid[6][2] = d;
    grid[8][4] = d;
    grid[7][8] = d;
}

void plugElementE(int e, int grid[GRID_SIZE][GRID_SIZE])
{
    grid[1][1] = e;
    grid[0][3] = e;
    grid[2][8] = e;
    grid[4][2] = e;
    grid[3][5] = e;
    grid[5][7] = e;
    grid[7][0] = e;
    grid[6][4] = e;
    grid[8][6] = e;
}

void plugElementF(int f, int grid[GRID_SIZE][GRID_SIZE])
{
    grid[2][1] = f;
    grid[1][5] = f;
    grid[0][8] = f;
    grid[5][0] = f;
    grid[4][3] = f;
    grid[3][7] = f;
    grid[8][2] = f;
    grid[7][4] = f;
    grid[6][6] = f;
}

void plugElementG(int g, int grid[GRID_SIZE][GRID_SIZE])
{
    grid[0][2] = g;
    grid[2][4] = g;
    grid[1][8] = g; //1.8
    grid[3][1] = g;
    grid[5][3] = g;
    grid[4][6] = g;
    grid[6][0] = g;
    grid[8][5] = g;
    grid[7][7] = g;
}

void plugElementH(int h, int grid[GRID_SIZE][GRID_SIZE])
{
    grid[1][0] = h;
    grid[0][4] = h;
    grid[2][6] = h;
    grid[4][1] = h;
    grid[3][3] = h;
    grid[5][8] = h;
    grid[7][2] = h;
    grid[6][5] = h;
    grid[8][7] = h;
}

void plugElementI(int i, int grid[GRID_SIZE][GRID_SIZE])
{
    grid[2][2] = i;
    grid[1][4] = i;
    grid[0][6] = i;
    grid[5][1] = i;
    grid[4][5] = i;
    grid[3][8] = i;
    grid[8][0] = i;
    grid[7][3] = i;
    grid[6][7] = i;
}

void plugAllElements(int a, int b, int c, int d, int e, int f,
                     int g, int h, int i, int sudokuGrid[GRID_SIZE][GRID_SIZE])
{
    plugElementA(a, sudokuGrid);
    plugElementB(b, sudokuGrid);
    plugElementC(c, sudokuGrid);
    plugElementD(d, sudokuGrid);
    plugElementE(e, sudokuGrid);
    plugElementF(f, sudokuGrid);
    plugElementG(g, sudokuGrid);
    plugElementH(h, sudokuGrid);
    plugElementI(i, sudokuGrid);
}
void plugAllElementsToAnother(int a, int b, int c, int d, int e, int f,
                              int g, int h, int i, int comparsionGrid[GRID_SIZE][GRID_SIZE])
{

    /* content of SudokuGrid is copied to a grid before deletion,
    to compare user solution to actual solution*/
    plugElementA(a, comparsionGrid);
    plugElementB(b, comparsionGrid);
    plugElementC(c, comparsionGrid);
    plugElementD(d, comparsionGrid);
    plugElementE(e, comparsionGrid);
    plugElementF(f, comparsionGrid);
    plugElementG(g, comparsionGrid);
    plugElementH(h, comparsionGrid);
    plugElementI(i, comparsionGrid);
}

void printTimer(int elapsedSeconds)
{
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;
    cout << "Time elapsed: " << minutes << " minutes " << seconds << " seconds" << endl;
}

int main()
{
    
    // Seed the random number generator
    int difficulty;
    cout << "Choose difficulty level:\n";
    cout << ANSI_GREEN << "1. Easy ^o^\n"
         << ANSI_RESET;
    cout << ANSI_YELLOW << "2. Intermediate       T_T\n"
         << ANSI_RESET;
    cout << ANSI_RED << "3. Hard    X_X\n"
         << ANSI_RESET;
    cout << ANSI_PURPLE << "4. Random        :-() \n"
         << ANSI_RESET;
    cout << ANSI_FLAME << "Any other key: Exit.\n\n"
         << ANSI_RESET;
    cout << "Enter your choice: ";
    cin >> difficulty;

    int numToDelete;
    switch (difficulty)
    {
    case 1:
        numToDelete = 2;
        break;
    case 2:
        numToDelete = 54;
        break;
    case 3:
        numToDelete = 63;
        break;
    case 4:
        numToDelete = rand() % 65 + 1;
        break;
    default:
        cout << "Invalid choice. Exiting...\n";
        return 1;
    }

    // Initialize variables
    int a, b, c, d, e, f, g, h, i;
    int sudokuGrid[GRID_SIZE][GRID_SIZE] = {0};
    int comparsionGrid[GRID_SIZE][GRID_SIZE] = {0};
    bool emptyCells[GRID_SIZE][GRID_SIZE] = {false};

    srand(time(0));
    // Assign random numbers to variables
    generateUniqueRandomNumbers(a, b, c, d, e, f, g, h, i);
    plugAllElements(a, b, c, d, e, f, g, h, i, sudokuGrid);
    plugAllElementsToAnother(a, b, c, d, e, f, g, h, i, comparsionGrid);

    cout << "\tSudoku Grid:\n\tLevel: ";

    printGrid(sudokuGrid, numToDelete, emptyCells);

    int row = 0, col = 0;
    int number;
    // initialize logic variables
    bool allCellsFilled;
    bool solutionValidated = false;
    bool puzzleSolved = false;
    time_t startTime = time(NULL);

    while (!puzzleSolved)
    {
        // Clear screen
        system("cls");
        int userScore = 0; 
        // Calculate elapsed time
        time_t currentTime = time(NULL);
        int elapsedSeconds = difftime(currentTime, startTime);
        printTimer(elapsedSeconds);
        printScore(elapsedSeconds, numToDelete, userScore);



        // Print instructions
        cout << ANSI_FLAME
             << "          Instructions       " << ANSI_RESET << endl;
        cout << "  ###########################" << endl;
        cout << "# Arrow Keys: Navigate      #" << endl;
        cout << "# Space: Select Cell        #" << endl;
        cout << "# BackSpace: Delete Cell    #" << endl;
        cout << "# E: Exit Game              #" << endl;
        cout << "# C: Confirm Solution       #" << endl;
        cout << "# Enter: Confirm Number     #" << endl;
        cout << "#Level: ";
        if (numToDelete == 2)
        {
            cout << ANSI_GREEN << "Easy              "
                 << ANSI_RESET << "  #\n";
        }
        else if (numToDelete == 54)
        {
            cout << ANSI_YELLOW << "Intermediate      "
                 << ANSI_RESET << "  #\n";
        }
        else if (numToDelete == 63)
        {
            cout << ANSI_RED << "Hard              "
                 << ANSI_RESET << "  #\n";
        }
        else
        {
            cout << ANSI_RED << "random            "
                 << ANSI_RESET << "  #\n";
        }
        cout << "###########################" << endl;

        // Print the Sudoku grid with current cursor position
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            for (int j = 0; j < GRID_SIZE; ++j)
            {
                if (i == row && j == col)
                {
                    cout << ANSI_RED << "[" << sudokuGrid[i][j] << "] " << ANSI_RESET;
                }
                else
                {
                    if (emptyCells[i][j] == false)
                    {
                        cout << ANSI_YELLOW << " " << sudokuGrid[i][j] << "  " << ANSI_RESET;
                    }
                    else
                    {
                        cout << ANSI_ORANGE << " " << sudokuGrid[i][j] << "  " << ANSI_RESET;
                    }
                }
                if ((j + 1) % 3 == 0 && j != GRID_SIZE - 1)
                {
                    cout << ANSI_D_BLUE << "| " << ANSI_RESET; // Print vertical line after every 3 columns
                }
            }
            cout << endl;
            if ((i + 1) % 3 == 0 && i != GRID_SIZE - 1)
            {
                cout << ANSI_PURPLE << "------------+-------------+------------" << ANSI_RESET << endl; // Print horizontal line after every 3 rows
            }
        }

        // Get user input
        char input = _getch();
        switch (input)
        {
        case ' ':
        handleInput(number, emptyCells, sudokuGrid, row, col);
        break;
    case 'C': // Confirm solution
    case 'c':
        confirmSolution(sudokuGrid, comparsionGrid, allCellsFilled, solutionValidated, puzzleSolved, elapsedSeconds, userScore, numToDelete);
        break;
    case 'E':
    case 'e':
        exitGame(puzzleSolved);
        break;

            // Inside the switch statement case 8 (backspace)
        case 8: // ASCII value for backspace
            // Clear the cell if it's not an original puzzle cell
            if (emptyCells[row][col])
            {
                sudokuGrid[row][col] = 0;
            }
            break;
        case 72: // Up arrow key
            if (row > 0)
            {
                row--;
            }
            break;
        case 80: // Down arrow key
            if (row < GRID_SIZE - 1)
            {
                row++;
            }
            break;
        case 75: // Left arrow key
            if (col > 0)
            {
                col--;
            }
            break;
        case 77: // Right arrow key
            if (col < GRID_SIZE - 1)
            {
                col++;
            }
            break;
            // Ignore other keys
            break;
        }
    }

    system("pause");
    return 0;
}


