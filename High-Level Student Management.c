#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

// Structure to hold student data
typedef struct {
    int id;
    char name[50];
    float gpa;
} Student;

// Function Prototypes
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Student by ID\n");
        printf("4. Update Student Record\n");
        printf("5. Delete Student Record\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: 
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default: 
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// 1. Function to Add a Student Record (Append Mode)
void addStudent() {
    FILE *fp = fopen(FILE_NAME, "ab"); // Open in append-binary mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Student s;
    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);
    getchar(); // Clear newline character from buffer
    printf("Enter Student Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; // Remove trailing newline
    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Record added successfully!\n");
}

// 2. Function to Display All Records
void displayStudents() {
    FILE *fp = fopen(FILE_NAME, "rb"); // Open in read-binary mode
    if (fp == NULL) {
        printf("\nNo records found. Please add a student first.\n");
        return;
    }

    Student s;
    printf("\n---------------------------------------------\n");
    printf("%-10s %-30s %-5s\n", "ID", "Name", "GPA");
    printf("---------------------------------------------\n");
    
    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("%-10d %-30s %-5.2f\n", s.id, s.name, s.gpa);
    }
    printf("---------------------------------------------\n");
    fclose(fp);
}

// 3. Function to Search for a Student by ID
void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    int searchId, found = 0;
    printf("\nEnter Student ID to search: ");
    scanf("%d", &searchId);

    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == searchId) {
            printf("\nRecord Found:\n");
            printf("ID: %d\nName: %s\nGPA: %.2f\n", s.id, s.name, s.gpa);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nStudent with ID %d not found.\n", searchId);
    }
    fclose(fp);
}

// 4. Function to Update a Record
void updateStudent() {
    FILE *fp = fopen(FILE_NAME, "rb+"); // Open for reading and writing
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    int updateId, found = 0;
    printf("\nEnter Student ID to update: ");
    scanf("%d", &updateId);

    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == updateId) {
            found = 1;
            
            printf("\nCurrent Data - Name: %s, GPA: %.2f\n", s.name, s.gpa);
            getchar(); // Clear buffer
            printf("Enter New Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;
            printf("Enter New GPA: ");
            scanf("%f", &s.gpa);

            // Move file pointer back to the start of this specific record
            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            printf("\nRecord updated successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("\nStudent with ID %d not found.\n", updateId);
    }
    fclose(fp);
}

// 5. Function to Delete a Record (Using a Temporary File)
void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    FILE *tempFp = fopen("temp.txt", "wb");
    if (tempFp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    int deleteId, found = 0;
    printf("\nEnter Student ID to delete: ");
    scanf("%d", &deleteId);

    Student s;
    // Copy all records EXCEPT the one to delete over to the temporary file
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == deleteId) {
            found = 1; // Skip writing this record
        } else {
            fwrite(&s, sizeof(Student), 1, tempFp);
        }
    }

    fclose(fp);
    fclose(tempFp);

    if (found) {
        remove(FILE_NAME);       // Delete original file
        rename("temp.txt", FILE_NAME); // Rename temp file to replace original
        printf("\nRecord deleted successfully!\n");
    } else {
        remove("temp.txt"); // Clean up temporary file
        printf("\nStudent with ID %d not found.\n", deleteId);
    }
}