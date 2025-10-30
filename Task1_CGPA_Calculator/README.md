# CGPA Calculator

The CGPA Calculator reads course data either from a text file or directly from keyboard input,  
processes valid grades and credits, and computes the Cumulative Grade Point Average (CGPA) 
to two decimal places.

## Input Format

When reading from a file, each input follows this structure:
<number_of_courses>
<grade_1> <credits_1>
<grade_2> <credits_2>
...

Grades above 10 are capped, and invalid or negative entries are ignored automatically.  
If no input file is found, the program switches to manual input mode, prompting the user  
to enter the number of courses, grades, and credits directly from the console.

## CGPA Calculation Logic

For each valid course:
grade_points = grade × credits

Then compute: 
CGPA = (sum of grade_points) / (sum of credits)

All values are rounded to two decimals for consistency:
cgpa = round(cgpa * 100) / 100.0;

Invalid lines, zero credits, or grades < 0 are ignored.

## Running the Program
    1. File Input Mode (default)
   
    g++ cgpa.cpp -o cgpa
    ./cgpa test1_normal.in
    cat cgpa.out

    2. Manual Input Mode
   
    If the input file does not exist, the program automatically asks for input from the keyboard:

    File not found. Switching to manual input mode.
    Enter number of courses: 3
    Course 1 grade and credits: 10 5
    Course 2 grade and credits: 9.5 6
    Course 3 grade and credits: 8 4
    ---------------------
    Total Credits: 15
    CGPA: 9.27

## Running Automated Tests

./run_tests.sh

The script compiles the program, runs all test input files,
and compares only the last line (CGPA:) from each .out and .ref file.
This ensures compatibility with the human-readable output format while keeping validation strict.
