#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <conio.h> 
#include <limits> // fpr  numeric_limits
#define GRID_SIZE 9
using namespace std;


// Initialize Ansi Colors
const string ANSI_RESET = "\033[0m";
const string ANSI_RED = "\033[1;31m";
const string ANSI_YELLOW = "\033[1;33m";
const string ANSI_PURPLE = "\033[1;35m";
const string ANSI_ORANGE = "\033[38;5;208m";
const string ANSI_GREEN = "\033[1;32m";


bool validateInput(int& number) {
    cin >> number;
    if (cin.fail()) {
        // Clear input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number." << endl;
        return false;
    }

    return true;
}

void handleInput(int& number, int sudokuGrid[GRID_SIZE][GRID_SIZE], int row, int col) {
    if (sudokuGrid[row][col] == 0) {
        cout << "Enter number: ";
        while (!validateInput(number)) {
            cout << "Enter number: ";
        }
        sudokuGrid[row][col] = number;
    }
    else {
        cout << "Do you want to erase the number? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            sudokuGrid[row][col] = 0; // Erase the number
        }
    }
}
// Function to print the Sudoku grid
void printGrid(int grid[GRID_SIZE][GRID_SIZE], int numToDelete, int localize[GRID_SIZE][GRID_SIZE]) {
    // Delete elements randomly
    srand(time(0));

    for (int k = 0; k < numToDelete; ++k) {
        int row = rand() % GRID_SIZE;
        int col = rand() % GRID_SIZE;
        grid[row][col] = 0; // Set the element to 0 to indicate it's empty
        localize[row][col] = true; // used for color mapping of ansi
    }

    // Print the grid
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] != 0) {
                cout << ANSI_YELLOW << grid[i][j] << " " << ANSI_RESET;
            }
            else {
                cout << "  ";
            }
            if ((j + 1) % 3 == 0 && j != GRID_SIZE - 1) {
                cout << ANSI_PURPLE << "| " << ANSI_RESET; // Print vertical line after every 3 columns
            }
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i != GRID_SIZE - 1) {
            cout << ANSI_PURPLE << "------+-------+------" << ANSI_RESET << endl; // Print horizontal line after every 3 rows
        }
    }
}


void plugElementA(int a, int grid[GRID_SIZE][GRID_SIZE]) {
    grid[0][0] = a; grid[1][3] = a; grid[2][7] = a;
    grid[3][2] = a; grid[4][4] = a; grid[5][6] = a;
    grid[6][1] = a; grid[7][5] = a; grid[8][8] = a;
}

void plugElementB(int b, int grid[GRID_SIZE][GRID_SIZE]) {
    grid[1][2] = b; grid[2][5] = b; grid[0][7] = b;
    grid[4][0] = b; grid[5][4] = b; grid[3][6] = b;
    grid[7][1] = b; grid[8][3] = b; grid[6][8] = b;
}

void plugElementC(int c, int grid[GRID_SIZE][GRID_SIZE]) {
    grid[2][0] = c; grid[0][5] = c; grid[1][7] = c;
    grid[5][2] = c; grid[3][4] = c; grid[4][8] = c;
    grid[8][1] = c; grid[6][3] = c; grid[7][6] = c;
}

void plugElementD(int d, int grid[GRID_SIZE][GRID_SIZE]) {
    grid[0][1] = d; grid[2][3] = d; grid[1][6] = d;
    grid[3][0] = d; grid[5][5] = d; grid[4][7] = d;
    grid[6][2] = d; grid[8][4] = d; grid[7][8] = d;
}

void plugElementE(int e, int grid[GRID_SIZE][GRID_SIZE]) {
    grid[1][1] = e; grid[0][3] = e; grid[2][8] = e;
    grid[4][2] = e; grid[3][5] = e; grid[5][7] = e;
    grid[7][0] = e; grid[6][4] = e; grid[8][6] = e;
}

void plugElementF(int f, int grid[GRID_SIZE][GRID_SIZE]) {
    grid[2][1] = f; grid[1][5] = f; grid[0][8] = f;
    grid[5][0] = f; grid[4][3] = f; grid[3][7] = f;
    grid[8][2] = f; grid[7][4] = f; grid[6][6] = f;
}

void plugElementG(int g, int grid[GRID_SIZE][GRID_SIZE]) {
    grid[0][2] = g; grid[2][4] = g; grid[0][6] = g;
    grid[3][1] = g; grid[5][3] = g; grid[4][6] = g;
    grid[6][0] = g; grid[8][5] = g; grid[7][7] = g;
}

void plugElementH(int h, int grid[GRID_SIZE][GRID_SIZE]) {
    grid[1][0] = h; grid[0][4] = h; grid[2][6] = h;
    grid[4][1] = h; grid[3][3] = h; grid[5][8] = h;
    grid[7][2] = h; grid[6][5] = h; grid[8][7] = h;
}

void plugElementI(int i, int grid[GRID_SIZE][GRID_SIZE]) {
    grid[2][2] = i; grid[1][4] = i; grid[1][8] = i;
    grid[5][1] = i; grid[4][5] = i; grid[3][8] = i;
    grid[8][0] = i; grid[7][3] = i; grid[6][7] = i;
}

void plugAllElements(int a, int b, int c, int d, int e, int f,
    int g, int h, int i, int sudokuGrid[][9]) {
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

int main() {
    // Seed the random number generator
    cout << ANSI_RED << "                                         Guide to how to play the game... \n" << ANSI_RESET;
    cout << ANSI_RED << "After determining the difficulty of the game use the arrows to navigate the place where you want to put your number then press (space) to select the cell, you will be asked to enter the number. Enter it, then press (enter), and so on. \n" << ANSI_RESET;
    cout << endl;

    int difficulty;
    cout << "Choose difficulty level:\n";
    cout << ANSI_GREEN << "1. Easy\n" << ANSI_RESET;
    cout << ANSI_YELLOW << "2. Intermediate\n" << ANSI_RESET;
    cout << ANSI_RED << "3. Hard\n" << ANSI_RESET;
    cout << "Enter your choice: ";
    cin >> difficulty;

    int numToDelete;
    switch (difficulty) {
    case 1:
        numToDelete = 30;
        break;
    case 2:
        numToDelete = 54;
        break;
    case 3:
        numToDelete = 63;
        break;
    default:
        cout << "Invalid choice. Exiting...\n";
        return 1;
    }

    // Initialize variables
    int a, b, c, d, e, f, g, h, i;
    int sudokuGrid[GRID_SIZE][GRID_SIZE] = { 0 };
    int emptyCells[GRID_SIZE][GRID_SIZE] = { false };



    srand(time(0));
    // Assign random numbers to variables
    a = rand() % 9 + 1;
    b = rand() % 9 + 1;
    while (b == a) b = rand() % 9 + 1;
    c = rand() % 9 + 1;
    while (c == a || c == b) c = rand() % 9 + 1;
    d = rand() % 9 + 1;
    while (d == a || d == b || d == c) d = rand() % 9 + 1;
    e = rand() % 9 + 1;
    while (e == a || e == b || e == c || e == d) e = rand() % 9 + 1;
    f = rand() % 9 + 1;
    while (f == a || f == b || f == c || f == d || f == e) f = rand() % 9 + 1;
    g = rand() % 9 + 1;
    while (g == a || g == b || g == c || g == d || g == e || g == f) g = rand() % 9 + 1;
    h = rand() % 9 + 1;
    while (h == a || h == b || h == c || h == d || h == e || h == f || h == g) h = rand() % 9 + 1;
    i = rand() % 9 + 1;
    while (i == a || i == b || i == c || i == d || i == e || i == f || i == g || i == h) i = rand() % 9 + 1;

    plugAllElements(a, b, c, d, e, f, g, h, i, sudokuGrid);


    cout << "\tSudoku Grid:\n\tLevel: ";
   

    printGrid(sudokuGrid, numToDelete, emptyCells);
    int row = 0, col = 0;
    int number;


    //KABALLO PART ( *TIMER* )
    int minutes = 59;
    int seconds = 59;
    int timer;
    timer = (minutes != 0) ? minutes * 60 : 0;
    timer += seconds;
 
    for (int i = timer; i > 0; i--) {

        cout << "                                                The time remaining " << minutes << ":" << seconds << endl;
        minutes = (i % 60 == 0) ? --minutes : minutes;
        seconds = (seconds == 0) ? 59 : --seconds;
        system("TIMEOUT 1");
        system("cls");
    //************************//
    }
    while (true) {
        // Clear screen
        system("cls");

        // Print instructions
        cout << "Arrow Keys: Navigate\n";
        cout << "Space: Select Cell\n";
        cout << "Enter: Confirm Number\n";
        cout << "\tSudoku Grid:\n\tLevel: ";


        if (numToDelete == 30) { cout << ANSI_GREEN << "Easy\n" << ANSI_RESET; }
        else if (numToDelete == 54) { cout << ANSI_YELLOW << "Intermediate\n" << ANSI_RESET; }
        else if (numToDelete == 63) { cout << ANSI_RED << "Hard\n" << endl << ANSI_RESET; }



        // Print the Sudoku grid with current cursor position
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                if (i == row && j == col) {
                    cout << ANSI_RED << "[" << sudokuGrid[i][j] << "] " << ANSI_RESET;
                }
                else {
                    if (emptyCells[i][j] == false) {
                        cout << ANSI_YELLOW << " " << sudokuGrid[i][j] << "  " << ANSI_RESET;
                    }
                    else {
                        cout << ANSI_ORANGE << " " << sudokuGrid[i][j] << "  " << ANSI_RESET;
                    }
                }
                if ((j + 1) % 3 == 0 && j != GRID_SIZE - 1) {
                    cout << ANSI_PURPLE << "| " << ANSI_RESET; // Print vertical line after every 3 columns
                }
            }
            cout << endl;
            if ((i + 1) % 3 == 0 && i != GRID_SIZE - 1) {
                cout << ANSI_PURPLE << "------------+-------------+------------" << ANSI_RESET << endl; // Print horizontal line after every 3 rows
            }
        }

        // Get user input
        char input = _getch();
        switch (input) {
        case ' ':
            handleInput(number, sudokuGrid, row, col);
            break;

            // Inside the switch statement case 8 (backspace)
        case 8: // ASCII value for backspace
            // Clear the cell if it's not an original puzzle cell
            if (emptyCells[row][col]) {
                sudokuGrid[row][col] = 0;
            }
            break;
        case 72: // Up arrow key
            if (row > 0) {
                row--;
            }
            break;
        case 80: // Down arrow key
            if (row < GRID_SIZE - 1) {
                row++;
            }
            break;
        case 75: // Left arrow key
            if (col > 0) {
                col--;
            }
            break;
        case 77: // Right arrow key
            if (col < GRID_SIZE - 1) {
                col++;
            }
            break;
        default:
            // Ignore other keys
            break;
        }

    }

    system("pause");
    return 0;
}