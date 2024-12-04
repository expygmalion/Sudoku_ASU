
# C++ Sudoku Game
An implementation of the famous Sudoku puzzle in a Windows console using C++.
This is a console-based Sudoku game implemented in C++ with interactive gameplay, difficulty levels, and a scoring system.

## Features

### Multiple Difficulty Levels
- **Easy**: 2 cells deleted (Just For Illustration)
- **Intermediate**: 54 cells deleted
- **Hard**: 63 cells deleted
- **Random Difficulty**: Removable N cells, adjustable by setting `difficultyOffset`.

### Interactive Gameplay
- **Keyboard navigation**: Arrow keys to move through the grid.
- **Cell selection and editing**: Space bar to select or edit a cell.
- **Timer tracking**: The game tracks time taken to complete.
- **Score calculation**: Based on time and number of deleted cells.

### Puzzle Generation
The puzzle follows a specific generation pattern designed for ease of solving. This pattern was developed when I was 13 years old.

### Game Controls
#### User keyboard interactions:
- **Arrow Keys**: Navigate grid
- **Space**: Select/Edit cell
- **Backspace**: Delete cell content
- **Enter**: Confirm solution
- **Esc**: Exit game

### Scoring
Score is calculated based on:
- Number of deleted cells
- Time taken to solve the puzzle

## Dependencies
This program uses the C++ Standard Library, and only one external library: **Windows-specific console input** (`<conio.h>`).

### Code for console input (via `<conio.h>`):
```cpp
#include <conio.h>  // Contains functions for non-buffered console input (_getch() on Windows)

// Example usage to capture a key press
char key = _getch();
if (key == 27) { // 27 is ASCII for the Esc key
    exitGame(puzzleSolved);
}
```

## Compilation
Compile the program with a C++ compiler that supports C++11 or later:
```bash
g++ -std=c++11 sudoku.cpp -o sudoku
```

## Running the Game
Run the compiled game:
```bash
./sudoku
```

## Limitations
- Currently designed for **Windows** (uses `<conio.h>`).
- Console-based interface.
- Requires console with **ANSI color** support.

### Code for ANSI color output:
```cpp
const string ANSI_RESET = "[0m";
const string ANSI_RED = "[1;31m";
const string ANSI_YELLOW = "[1;33m";
const string ANSI_PURPLE = "[1;35m";
const string ANSI_ORANGE = "[38;5;208m";
const string ANSI_GREEN = "[1;32m";
```

## Future Improvements
- Improved generation pattern.
- Cross-platform support.
- Persistent high score storage.
- More sophisticated puzzle generation.
- Hints and solver assistance.

## License
MIT License

## Author
Taj Othman
