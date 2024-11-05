#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define FILE_NAME "programs_setting.txt"

// Color codes for terminal output
#define COLOR_RESET "\033[0m"
#define COLOR_SUCCESS "\033[32m" // Green
#define COLOR_ERROR "\033[31m"   // Red
#define COLOR_INFO "\033[34m"    // Blue

// Program structure
typedef struct {
    int program_id;
    char program_code[20];
    char program_name[50];
    char program_desc[100];
} Program;

// Global array to store program data and a counter
Program programs[MAX];
int program_count = 0;

// Function declarations
void The_code_rangers_load_from_file();
void The_code_rangers_store_to_file();
void The_code_rangers_create_program();
void The_code_rangers_update_program();
void The_code_rangers_retrieve_programs();
void The_code_rangers_delete_program();
void The_code_rangers_search_by_field();
void The_code_rangers_sort_by_field();
void The_code_rangers_compare_sorting_algorithms();
void The_code_rangers_compare_searching_algorithms();
void The_code_rangers_display_time_complexity();
void The_code_rangers_display_pseudocode();
void The_code_rangers_display_menu();
void The_code_rangers_display_help();
void The_code_rangers_manual_store_to_file(); // New function for manual storage
int The_code_rangers_is_unique_id(int id);
void The_code_rangers_bubble_sort(const char *field);
void The_code_rangers_selection_sort(const char *field);
int The_code_rangers_linear_search(int id);
int The_code_rangers_binary_search(int id);
void The_code_rangers_display_table();

// Function to clear the input buffer
void The_code_rangers_clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Main function
int main() {
    The_code_rangers_load_from_file();
    The_code_rangers_display_menu();
    return 0;
}

// Function to display all programs in a tabular format
void The_code_rangers_display_table() {
    if (program_count == 0) {
        printf(COLOR_ERROR "No programs to display.\n" COLOR_RESET);
        return;
    }

    // Print table header
    printf("\n+-----+------------+--------------------+------------------------------+----------------------------------------+\n");
    printf("| No. | Program ID | Program Code       | Program Name                 | Description                            |\n");
    printf("+-----+------------+--------------------+------------------------------+----------------------------------------+\n");

    // Print each program entry in a row
    for (int i = 0; i < program_count; i++) {
        printf("| %-3d | %-10d | %-18s | %-28s | %-38s |\n",
               i + 1,
               programs[i].program_id,
               programs[i].program_code,
               programs[i].program_name,
               programs[i].program_desc);
    }

    // Print table footer
    printf("+-----+------------+--------------------+------------------------------+----------------------------------------+\n");
}

// Function to load data from file with error handling
void The_code_rangers_load_from_file() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Error opening file. Starting with an empty record.");
        return;
    }
    program_count = 0;
    while (fscanf(file, "%d %19s %49s %[^\n]", 
                  &programs[program_count].program_id, 
                  programs[program_count].program_code, 
                  programs[program_count].program_name, 
                  programs[program_count].program_desc) != EOF) {
        program_count++;
    }
    fclose(file);
    printf(COLOR_SUCCESS "Data loaded successfully from file.\n" COLOR_RESET);
    The_code_rangers_display_table();
}

// Function to store data to file with error handling
void The_code_rangers_store_to_file() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        perror("Error opening file for saving");
        return;
    }
    for (int i = 0; i < program_count; i++) {
        fprintf(file, "%d %s %s %s\n", programs[i].program_id, programs[i].program_code, 
                programs[i].program_name, programs[i].program_desc);
    }
    fclose(file);
    printf(COLOR_SUCCESS "Data saved to file.\n" COLOR_RESET);
}

// Function for manual storage of data to file
void The_code_rangers_manual_store_to_file() {
    The_code_rangers_store_to_file(); // Call the existing store_to_file function
}

// Check if the Program ID is unique
int The_code_rangers_is_unique_id(int id) {
    for (int i = 0; i < program_count; i++) {
        if (programs[i].program_id == id) {
            return 0; // ID is not unique
        }
    }
    return 1; // ID is unique
}

// Function to create a new program record with error handling
void The_code_rangers_create_program() {
    if (program_count >= MAX) {
        printf(COLOR_ERROR "Program list is full!\n" COLOR_RESET);
        return;
    }
    Program p;
    int id_valid = 0;

    // Read Program ID with validation
    while (!id_valid) {
        printf("Enter Program ID (integer): ");
        if (scanf("%d", &p.program_id) == 1 && The_code_rangers_is_unique_id(p.program_id)) {
            id_valid = 1;
        } else {
            printf(COLOR_ERROR "Invalid input or ID already exists. Please enter a unique integer.\n" COLOR_RESET);
            The_code_rangers_clear_input_buffer();
        }
    }
    The_code_rangers_clear_input_buffer();

    // Read Program Code
    printf("Enter Program Code: ");
    if (scanf("%19s", p.program_code) != 1) {
        printf(COLOR_ERROR "Error reading Program Code. Please try again.\n" COLOR_RESET);
        return;
    }
    The_code_rangers_clear_input_buffer();

    // Read Program Name
    printf("Enter Program Name: ");
    if (scanf("%49s", p.program_name) != 1) {
        printf(COLOR_ERROR "Error reading Program Name. Please try again.\n" COLOR_RESET);
        return;
    }
    The_code_rangers_clear_input_buffer();

    // Read Program Description
    printf("Enter Program Description: ");
    if (scanf(" %99[^\n]", p.program_desc) != 1) {
        printf(COLOR_ERROR "Error reading Program Description. Please try again.\n" COLOR_RESET);
        return;
    }

    programs[program_count++] = p;
    printf(COLOR_SUCCESS "Program created successfully!\n" COLOR_RESET);
}

// Update a program record with error handling
void The_code_rangers_update_program() {
    int id;
    int found = 0;

    printf("Enter Program ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf(COLOR_ERROR "Invalid input. Please enter an integer.\n" COLOR_RESET);
        The_code_rangers_clear_input_buffer();
        return;
    }
    The_code_rangers_clear_input_buffer();

    for (int i = 0; i < program_count; i++) {
        if (programs[i].program_id == id) {
            found = 1;
            printf("Enter new Program Code: ");
            scanf("%19s", programs[i].program_code);
            The_code_rangers_clear_input_buffer();
            printf("Enter new Program Name: ");
            scanf("%49s", programs[i].program_name);
            The_code_rangers_clear_input_buffer();
            printf("Enter new Program Description: ");
            scanf(" %99[^\n]", programs[i].program_desc);

            printf(COLOR_SUCCESS "Program updated successfully!\n" COLOR_RESET);
            break;
        }
    }
    if (!found) {
        printf(COLOR_ERROR "Program with ID %d not found.\n" COLOR_RESET, id);
    }
}

// Retrieve and display all program records with validation
void The_code_rangers_retrieve_programs() {
    if (program_count == 0) {
        printf(COLOR_ERROR "No programs to display.\n" COLOR_RESET);
        return;
    }
    printf("\nList of Programs:\n");
    // for (int i = 0; i < program_count; i++) {
    //     printf("ID: %d\nCode: %s\nName: %s\nDescription: %s\n\n",
    //            programs[i].program_id, programs[i].program_code,
    //            programs[i].program_name, programs[i].program_desc);
    // }
    The_code_rangers_display_table();
}

// Delete a program record with error handling
void The_code_rangers_delete_program() {
    int id;
    int found = 0;

    printf("Enter Program ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf(COLOR_ERROR "Invalid input. Please enter an integer.\n" COLOR_RESET);
        The_code_rangers_clear_input_buffer();
        return;
    }
    The_code_rangers_clear_input_buffer();

    for (int i = 0; i < program_count; i++) {
        if (programs[i].program_id == id) {
            found = 1;
            for (int j = i; j < program_count - 1; j++) {
                programs[j] = programs[j + 1];
            }
            program_count--;
            printf(COLOR_SUCCESS "Program deleted successfully!\n" COLOR_RESET);
            break;
        }
    }
    if (!found) {
        printf(COLOR_ERROR "Program with ID %d not found.\n" COLOR_RESET, id);
    }
}



// Helper function to convert a string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Search program by a specified field with substring matching (case-insensitive)
void The_code_rangers_search_by_field() {
    char input[50];
    int found = 0, choice;

    printf("Choose field to search by:\n1. Program Code\n2. Program Name\nEnter choice: ");
    scanf("%d", &choice);
    The_code_rangers_clear_input_buffer();

    printf("Enter part of the text to search: ");
    if (scanf("%49s", input) != 1) {
        printf(COLOR_ERROR "Error reading input.\n" COLOR_RESET);
        The_code_rangers_clear_input_buffer();
        return;
    }
    The_code_rangers_clear_input_buffer();
    to_lowercase(input); // Convert input to lowercase

    for (int i = 0; i < program_count; i++) {
        char field_text[50];

        if (choice == 1) {
            strncpy(field_text, programs[i].program_code, sizeof(field_text) - 1);
        } else if (choice == 2) {
            strncpy(field_text, programs[i].program_name, sizeof(field_text) - 1);
        } else {
            printf(COLOR_ERROR "Invalid choice.\n" COLOR_RESET);
            return;
        }
        field_text[sizeof(field_text) - 1] = '\0'; // Ensure null termination
        to_lowercase(field_text); // Convert field text to lowercase

        if (strstr(field_text, input) != NULL) { // Case-insensitive match
            printf("ID: %d\nCode: %s\nName: %s\nDescription: %s\n\n",
                   programs[i].program_id, programs[i].program_code,
                   programs[i].program_name, programs[i].program_desc);
            found = 1;
        }
    }

    if (!found) {
        printf(COLOR_INFO "No matching program found.\n" COLOR_RESET);
    }
}



// Sort programs by a specified field using a chosen algorithm
void The_code_rangers_sort_by_field() {
    char field[20];
    int algorithm_choice;

    printf("Choose sorting algorithm:\n1. Bubble Sort\n2. Selection Sort\nEnter choice: ");
    scanf("%d", &algorithm_choice);
    The_code_rangers_clear_input_buffer();

    printf("Enter field to sort by (code, name): ");
    scanf("%19s", field);
    The_code_rangers_clear_input_buffer();

    if (algorithm_choice == 1) {
        The_code_rangers_bubble_sort(field);
    } else if (algorithm_choice == 2) {
        The_code_rangers_selection_sort(field);
    } else {
        printf(COLOR_ERROR "Invalid sorting algorithm choice.\n" COLOR_RESET);
    }
}

// Bubble sort implementation for programs
void The_code_rangers_bubble_sort(const char *field) {
    for (int i = 0; i < program_count - 1; i++) {
        for (int j = 0; j < program_count - i - 1; j++) {
            int compare = 0;
            if (strcmp(field, "code") == 0) {
                compare = strcmp(programs[j].program_code, programs[j + 1].program_code);
            } else if (strcmp(field, "name") == 0) {
                compare = strcmp(programs[j].program_name, programs[j + 1].program_name);
            }
            if (compare > 0) {
                Program temp = programs[j];
                programs[j] = programs[j + 1];
                programs[j + 1] = temp;
            }
        }
    }
    printf(COLOR_SUCCESS "Programs sorted by %s using Bubble Sort!\n" COLOR_RESET, field);
    The_code_rangers_retrieve_programs();
}

// Selection sort implementation for programs
void The_code_rangers_selection_sort(const char *field) {
    for (int i = 0; i < program_count - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < program_count; j++) {
            int compare = 0;
            if (strcmp(field, "code") == 0) {
                compare = strcmp(programs[j].program_code, programs[min_index].program_code);
            } else if (strcmp(field, "name") == 0) {
                compare = strcmp(programs[j].program_name, programs[min_index].program_name);
            }
            if (compare < 0) {
                min_index = j;
            }
        }
        Program temp = programs[min_index];
        programs[min_index] = programs[i];
        programs[i] = temp;
    }
    printf(COLOR_SUCCESS "Programs sorted by %s using Selection Sort!\n" COLOR_RESET, field);
    The_code_rangers_retrieve_programs();
}

// Compare sorting algorithms
void The_code_rangers_compare_sorting_algorithms() {
    char field[20];

    printf("Enter field to sort by for comparison (code, name): ");
    scanf("%19s", field);
    The_code_rangers_clear_input_buffer();

    printf("\nSorting using Bubble Sort:\n");
    The_code_rangers_bubble_sort(field);

    printf("\nSorting using Selection Sort:\n");
    The_code_rangers_selection_sort(field);
}



// Linear search implementation
int The_code_rangers_linear_search(int id) {
    for (int i = 0; i < program_count; i++) {
        if (programs[i].program_id == id) {
            return i;
        }
    }
    return -1; // Not found
}

// Binary search implementation
int The_code_rangers_binary_search(int id) {
    int left = 0, right = program_count - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (programs[mid].program_id == id) {
            return mid; // Found
        }
        if (programs[mid].program_id < id) {
            left = mid + 1; // Search right half
        } else {
            right = mid - 1; // Search left half
        }
    }
    return -1; // Not found
}

void The_code_rangers_compare_searching_algorithms() {
    int id_to_search;
    printf("Enter Program ID to search: ");
    scanf("%d", &id_to_search);
    The_code_rangers_clear_input_buffer();

    printf("Comparing searching algorithms...\n");

    // Linear search
    int linear_index = The_code_rangers_linear_search(id_to_search);
    if (linear_index != -1) {
        printf("Linear Search found Program ID %d at index %d.\n", id_to_search, linear_index);
    } else {
        printf("Linear Search did not find Program ID %d.\n", id_to_search);
    }

    // Binary search (assumes programs are sorted by ID)
    int binary_index = The_code_rangers_binary_search(id_to_search);
    if (binary_index != -1) {
        printf("Binary Search found Program ID %d at index %d.\n", id_to_search, binary_index);
    } else {
        printf("Binary Search did not find Program ID %d.\n", id_to_search);
    }
}


// Display time complexity for sorting and searching algorithms
void The_code_rangers_display_time_complexity() {
    printf("Time Complexity Analysis:\n");
    printf("Bubble Sort: O(n^2)\n");
    printf("Selection Sort: O(n^2)\n");
    printf("Linear Search: O(n)\n");
    printf("Binary Search: O(log n)\n");
}

// Display pseudocode for sorting and searching algorithms
void The_code_rangers_display_pseudocode() {
    printf("Pseudocode for Bubble Sort:\n");
    printf("for i from 0 to n-1\n");
    printf("   for j from 0 to n-i-1\n");
    printf("      if programs[j] > programs[j+1]\n");
    printf("         swap programs[j] and programs[j+1]\n\n");

    printf("Pseudocode for Selection Sort:\n");
    printf("for i from 0 to n-1\n");
    printf("   min_index = i\n");
    printf("   for j from i+1 to n\n");
    printf("      if programs[j] < programs[min_index]\n");
    printf("         min_index = j\n");
    printf("   swap programs[i] and programs[min_index]\n\n");

    printf("Pseudocode for Linear Search:\n");
    printf("for each element in programs\n");
    printf("   if element matches search criteria\n");
    printf("      return element\n\n");
}

// Display help information
void The_code_rangers_display_help() {
    printf("Help Menu:\n");
    printf("1. Create Program: Add a new program to the list.\n");
    printf("2. Update Program: Modify an existing program's details.\n");
    printf("3. Retrieve Programs: Display all programs in the list.\n");
    printf("4. Delete Program: Remove a program from the list.\n");
    printf("5. Search by Field: Find a program using its code or name.\n");
    printf("6. Sort by Field: Organize programs based on code or name.\n");
    printf("7. Compare Sorting Algorithms: Compare performance of sorting methods.\n");
    printf("8. Display Time Complexity: Show time complexities of various algorithms.\n");
    printf("9. Display Pseudocode: View pseudocode for algorithms used.\n");
    printf("10. Manually Save to File: Save program data to a file manually.\n");
    printf("11. Exit: Close the program.\n");
}

// Display menu and handle choices with validation
void The_code_rangers_display_menu() {
    int choice;
    do {
        printf("\n1. Create Program\n2. Update Program\n3. Retrieve Programs\n4. Delete Program\n");
        printf("5. Search by Field\n6. Sort by Field\n7. Compare Sorting Algorithms\n");
        printf("8. Compare Searching Algorithms\n");
        printf("9. Display Time Complexity\n10. Display Pseudocode\n11. Store/Save to File\n12. Help\n13. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf(COLOR_ERROR "Invalid input. Please enter a number between 1 and 12.\n" COLOR_RESET);
            The_code_rangers_clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1: The_code_rangers_create_program(); break;
            case 2: The_code_rangers_update_program(); break;
            case 3: The_code_rangers_retrieve_programs(); break;
            case 4: The_code_rangers_delete_program(); break;
            case 5: The_code_rangers_search_by_field(); break;
            case 6: The_code_rangers_sort_by_field(); break;
            case 7: The_code_rangers_compare_sorting_algorithms(); break;
            case 8: The_code_rangers_compare_searching_algorithms(); break;
            case 9: The_code_rangers_display_time_complexity(); break;
            case 10: The_code_rangers_display_pseudocode(); break;
            case 11: The_code_rangers_manual_store_to_file(); break; // New case for manual saving
            case 12: The_code_rangers_display_help(); break;
            case 13: printf(COLOR_SUCCESS "Exiting program.\n" COLOR_RESET); exit(0);
            
            default: printf(COLOR_ERROR "Invalid choice! Please enter a number between 1 and 12.\n" COLOR_RESET);
        }
    } while (choice != 12);
}

