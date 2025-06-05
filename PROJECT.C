#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student data
struct Student {
    int roll;
    char name[50];
    float marks;
};

// Function to add a student record
void addStudent() {
    FILE *fp = fopen("students.dat", "ab");  // Open file in append binary mode
    struct Student s;

    // Input student details
    printf("\nEnter Roll: ");
    scanf("%d", &s.roll);
    getchar(); // To consume leftover newline from input buffer

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin); // Get student name
    s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline character

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    // Write student data to file
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp); // Close the file
    printf("Student Added!\n");
}

// Function to view all student records
void viewStudents() {
    FILE *fp = fopen("students.dat", "rb");  // Open file in read binary mode
    struct Student s;

    printf("\n--- Student List ---\n");

    // Read and display all records
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp); // Close the file
}

// Function to search for a student by roll number
void searchStudent() {
    int roll, found = 0;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");

    printf("Enter Roll to Search: ");
    scanf("%d", &roll);

    // Search student in file
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Found: %s - %.2f Marks\n", s.name, s.marks);
            found = 1;
            break;
        }
    }

    fclose(fp); // Close file

    if (!found)
        printf("Student Not Found!\n");
}

// Main function: Menu system
int main() {
    int ch;

    // Loop until user exits
    do {
        // Show menu
        printf("\n1. Add Student\n2. View Students\n3. Search Student\n4. Exit\nChoose: ");
        scanf("%d", &ch);

        // Call functions based on user choice
        switch (ch) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (ch != 4);

    return 0;
}
