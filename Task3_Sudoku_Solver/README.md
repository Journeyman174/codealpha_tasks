# Sudoku Solver

The Sudoku Solver reads a 9×9 Sudoku grid from a file,  
applies a backtracking algorithm to fill in missing values,  
and outputs the solved puzzle both in the console (formatted)  
and in the `sudoku.out` file.

It accepts the input file name as a command-line argument  
and works on both Windows and Linux/macOS.

---

## Program Logic

1. **Input Handling**
   - Reads a 9×9 grid of integers from an input file (`.in`).
   - Empty cells are represented by `0`.
   - Validates input format and ensures values are between `0` and `9`.
   - Detects invalid configurations (duplicates in row, column, or 3×3 block).

2. **Sudoku Validation**
   - Checks that the initial puzzle does not break Sudoku rules.
   - Returns an error message if an invalid configuration is found:  
     `Invalid Sudoku configuration`

3. **Solving Algorithm**
   - Uses recursive backtracking:
     - Finds the first empty cell.
     - Tries numbers 1–9 that obey Sudoku rules.
     - Recursively continues until the puzzle is solved.
     - Performs automatic backtracking if no valid number fits.
   - Stops when a valid and complete grid is found.

4. **Output**
   - Prints the solved Sudoku in a formatted layout:
     ```
     -------------------------
     | 5 3 4 | 6 7 8 | 9 1 2 |
     | 6 7 2 | 1 9 5 | 3 4 8 |
     | 1 9 8 | 3 4 2 | 5 6 7 |
     -------------------------
     | 8 5 9 | 7 6 1 | 4 2 3 |
     | 4 2 6 | 8 5 3 | 7 9 1 |
     | 7 1 3 | 9 2 4 | 8 5 6 |
     -------------------------
     | 9 6 1 | 5 3 7 | 2 8 4 |
     | 2 8 7 | 4 1 9 | 6 3 5 |
     | 3 4 5 | 2 8 6 | 1 7 9 |
     -------------------------
     ```
   - Also writes the solution to the file `sudoku.out`.  
   - Displays appropriate error messages for invalid or unsolvable puzzles:  
     `No solution exists`

---

## Running the Program

- **Compilation**
  ```bash
  g++ sdk.cpp -o sudoku
  ```

- **Execution**
  ```bash
  ./sudoku sudokuX.in
  ```

- Each ./sudoku sudokuX.in command reads a different input file  
  and writes the solved puzzle to `sudoku.out`.

---

## Test Files Included

- `sudoku1.in` – Standard solvable puzzle  
- `sudoku2.in` – Already solved grid  
- `sudoku3.in` – Invalid configuration  
- `sudoku4.in` – All zeros (empty grid)  
- `sudoku5.in` – No valid solution  
- `sudoku6.in` – Hard puzzle with minimal clues  

---

## Checker Script

- A `checker.sh` script is provided to automatically:
  - Run the solver for all test files.
  - Compare each generated output (`sudoku.out`)  
    with its corresponding reference file (`.ref`).
  - Display **PASS / FAIL** for each test.

**Usage:**
```bash
chmod +x checker.sh
./checker.sh
```

---
