#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

void addStudent(FILE *fp) {
    struct Student s;
    printf("Enter Student of theirnID: ");
    scanf("%d", &s.id);
    printf("Enter Student Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);
    fwrite(&s, sizeof(s), 1, fp);
    printf("Student record added successfully.\n");
}

void displayStudents(FILE *fp) {
    struct Student s;
    rewind(fp);
    printf("\n%-10s %-20s %-10s\n", "ID", "Name", "Marks");
    printf("============================================\n");
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("%-10d %-20s %-10.2f\n", s.id, s.name, s.marks);
    }
}

int main() {
    FILE *fp;
    int choice;
    fp = fopen("students.dat", "ab+");
    if (!fp) {
        printf("Unable to open file!\n");
        return 1;
    }
    do {
        printf("\n1. Add Student\n2. Display Students\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addStudent(fp); break;
            case 2: displayStudents(fp); break;
            case 3: fclose(fp); printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 3);
    return 0;
}
