#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

const int N = 9;

// Check if a number can be placed safely in (row, col)
bool isValid(const vector<vector<int>>& grid, int row, int col, int num) {
    // Row check
    for (int x = 0; x < N; ++x)
        if (grid[row][x] == num)
            return false;

    // Column check
    for (int x = 0; x < N; ++x)
        if (grid[x][col] == num)
            return false;

    // 3x3 box check
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (grid[startRow + i][startCol + j] == num)
                return false;

    return true;
}

// Recursive backtracking solver
bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku(grid))
                            return true;
                        grid[row][col] = 0;
                    }
                }
                // no valid number -> backtrack
                return false; 
            }
        }
    }
    return true;
}

// Console print
void printSudokuConsole(const vector<vector<int>>& grid) {
    cout << "\nSolved Sudoku Puzzle:\n";
    cout << "-------------------------\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j % 3 == 0) cout << "| ";
            cout << grid[i][j] << " ";
        }
        cout << "|\n";
        if ((i + 1) % 3 == 0)
            cout << "-------------------------\n";
    }
}

// Check if current puzzle already violates Sudoku rules
bool isInitialGridValid(const vector<vector<int>>& grid) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int num = grid[i][j];
            if (num != 0) {
                // Temporarily clear current cell for checking
                vector<vector<int>> temp = grid;
                temp[i][j] = 0;
                if (!isValid(temp, i, j, num))
                    return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    // default fallback
    string inputFile = "sudoku.in";
    // constant output name   
    string outputFile = "sudoku.out"; 

    if (argc > 1) {
        // if provided as argument
        inputFile = argv[1]; 
    }

    ifstream fin(inputFile);
    ofstream fout(outputFile);

    if (!fin.is_open()) {
        cerr << "Error: cannot open " << inputFile << "\n";
        return 1;
    }

    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            if (!(fin >> grid[i][j])) {
                cerr << "Error: invalid input format at (" << i << "," << j << ")\n";
                return 1;
            }
            if (grid[i][j] < 0 || grid[i][j] > 9) {
                cerr << "Error: invalid number " << grid[i][j] << " at (" << i << "," << j << ")\n";
                return 1;
            }
        }

    // Validate initial puzzle
    if (!isInitialGridValid(grid)) {
        fout << "Invalid Sudoku configuration\n";
        cerr << "Invalid initial configuration detected.\n";
        return 0;
    }

    // Solve Sudoku
    if (solveSudoku(grid)) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j)
                fout << grid[i][j] << " ";
            fout << "\n";
        }
        printSudokuConsole(grid);
    } else {
        fout << "No solution exists\n";
        cerr << "No valid solution could be found.\n";
    }

    return 0;
}
