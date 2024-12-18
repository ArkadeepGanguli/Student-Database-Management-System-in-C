#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define DATABASE_FILE "students.txt"

// Structure to store student details
typedef struct {
    int rollNo;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    float GPA;
} Student;

// Function prototypes
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void updateStudent();
void loadDatabase();
void saveDatabase();

int main() {
    int choice;

    loadDatabase(); // Load data from file at startup

    while (1) {
        printf("\nStudent Database Management System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                updateStudent();
                break;
            case 6:
                saveDatabase(); // Save data to file before exiting
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addStudent() {
    Student s;
    printf("Enter roll number: ");
    scanf("%d", &s.rollNo);
    printf("Enter first name: ");
    scanf("%s", s.firstName);
    printf("Enter last name: ");
    scanf("%s", s.lastName);
    printf("Enter GPA: ");
    scanf("%f", &s.GPA);

    FILE *file = fopen(DATABASE_FILE, "a");
    if (file == NULL) {
        printf("Error opening database file!\n");
        return;
    }

    fprintf(file, "%d,%s,%s,%.2f\n", s.rollNo, s.firstName, s.lastName, s.GPA);
    fclose(file);

    printf("Student added successfully!\n");
}

void displayStudents() {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        printf("No student records to display.\n");
        return;
    }

    printf("\nStudent Records:\n");
    printf("Roll No\t\tFirst Name\t\tLast Name\t\tGPA\n");
    printf("---------------------------------------------------------------------\n");

    int rollNo;
    char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH];
    float GPA;

    while (fscanf(file, "%d,%[^,],%[^,],%f\n", &rollNo, firstName, lastName, &GPA) != EOF) {
        printf("%d\t\t%s\t\t%s\t\t\t%.2f\n", rollNo, firstName, lastName, GPA);
    }

    fclose(file);
}

void searchStudent() {
    int rollNo;
    printf("Enter roll number to search: ");
    scanf("%d", &rollNo);

    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        printf("No student records found.\n");
        return;
    }

    int found = 0;
    int r;
    char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH];
    float GPA;

    while (fscanf(file, "%d,%[^,],%[^,],%f\n", &r, firstName, lastName, &GPA) != EOF) {
        if (r == rollNo) {
            printf("\nStudent Found:\n");
            printf("Roll No: %d\n", r);
            printf("First Name: %s\n", firstName);
            printf("Last Name: %s\n", lastName);
            printf("GPA: %.2f\n", GPA);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with roll number %d not found.\n", rollNo);
    }

    fclose(file);
}

void deleteStudent() {
    int rollNo;
    printf("Enter roll number to delete: ");
    scanf("%d", &rollNo);

    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        printf("No student records found.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        return;
    }

    int r;
    char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH];
    float GPA;
    int found = 0;

    while (fscanf(file, "%d,%[^,],%[^,],%f\n", &r, firstName, lastName, &GPA) != EOF) {
        if (r == rollNo) {
            found = 1;
        } else {
            fprintf(tempFile, "%d,%s,%s,%.2f\n", r, firstName, lastName, GPA);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(DATABASE_FILE);
    rename("temp.txt", DATABASE_FILE);

    if (found) {
        printf("Student with roll number %d deleted successfully.\n", rollNo);
    } else {
        printf("Student with roll number %d not found.\n", rollNo);
    }
}

void updateStudent() {
    int rollNo;
    printf("Enter roll number to update: ");
    scanf("%d", &rollNo);

    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        printf("No student records found.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        return;
    }

    int r;
    char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH];
    float GPA;
    int found = 0;

    while (fscanf(file, "%d,%[^,],%[^,],%f\n", &r, firstName, lastName, &GPA) != EOF) {
        if (r == rollNo) {
            printf("Enter new first name: ");
            scanf("%s", firstName);
            printf("Enter new last name: ");
            scanf("%s", lastName);
            printf("Enter new GPA: ");
            scanf("%f", &GPA);
            fprintf(tempFile, "%d,%s,%s,%.2f\n", r, firstName, lastName, GPA);
            found = 1;
        } else {
            fprintf(tempFile, "%d,%s,%s,%.2f\n", r, firstName, lastName, GPA);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(DATABASE_FILE);
    rename("temp.txt", DATABASE_FILE);

    if (found) {
        printf("Student record updated successfully.\n");
    } else {
        printf("Student with roll number %d not found.\n", rollNo);
    }
}

void loadDatabase() {
    FILE *file = fopen(DATABASE_FILE, "a");
    if (file != NULL) {
        fclose(file);
    }
}

void saveDatabase() {
    // Placeholder function (all data is directly saved during each operation)
}
