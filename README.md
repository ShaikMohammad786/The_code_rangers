# The_code_rangers
Daa Project - program level objective setting

This C program provides a system to manage "programs" (e.g., software projects or educational courses) with functionalities to create, update, delete, retrieve, search, and sort program records. Data is stored and retrieved from a file, making the program’s state persistent between sessions.

Features
Create a New Program: Add a new record with a unique ID, code, name, and description.
Update Existing Programs: Modify the details of any existing program using its unique ID.
Retrieve Programs: Display all saved programs in a tabular format.
Delete a Program: Remove a specific program by ID.
Search Programs: Search by program code or name, with partial matching support.
Sort Programs: Sort records by program code or name using Bubble Sort or Selection Sort.
Compare Algorithms: Compare performance of sorting and searching algorithms.
Display Time Complexity: Show time complexity analysis of algorithms.
Manual Save to File: Store data to file manually at any point.
Load Data from File: Automatically load data from file on program startup.
Requirements
Compiler: Requires a C compiler, such as gcc.
System: Tested on Unix-based systems (Linux, macOS). Windows may require adjustments for color codes.
Installation
Clone this repository:

bash
Copy code
git clone https://github.com/yourusername/The-Code-Rangers.git
cd The-Code-Rangers
Compile the program:

bash
Copy code
gcc -o code_rangers main.c
Usage
Run the compiled program:

bash
Copy code
./code_rangers
Menu Options
Create Program: Enter unique ID, code, name, and description.
Update Program: Modify details by entering a valid ID.
Retrieve Programs: Display all records.
Delete Program: Remove by ID.
Search by Field: Search by code or name with partial match.
Sort by Field: Choose a field (code or name) and sorting algorithm.
Compare Sorting Algorithms: Perform a comparison of sorting methods.
Compare Searching Algorithms: Search for a program ID with Linear and Binary Search.
Display Time Complexity: View complexities of algorithms.
Display Pseudocode: See pseudocode for implemented algorithms.
Store/Save to File: Manually save data.
Help: Displays help menu.
Exit: Exit the program.
File Structure
The program data is stored in programs_setting.txt. Each line contains:

ID: Unique identifier for each program
Code: Short code for the program
Name: Name of the program
Description: Brief description of the program
Example File Content
arduino
Copy code
101 PRG101 Intro_Programming "Introduction to Programming"
102 PRG102 Data_Structures "Advanced data structures and algorithms"
Implementation Notes
Sorting Algorithms: Implements Bubble Sort and Selection Sort for educational purposes.
Searching Algorithms: Linear Search and Binary Search for comparison.
Error Handling: Includes input validation and error messages for user guidance.
ANSI Color Codes: Used for better visual feedback in the terminal.
