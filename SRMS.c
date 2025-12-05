#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "usersinfo.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};


char currentRole[10];
char currentUser[50];

void userpwdcheck();
int loginSystem();
void mainMenu();
void adminMenu();
void staffMenu();
void userMenu();
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void deleteAllStudents();

int main() {
    userpwdcheck();
    if (loginSystem()) {
        printf("\nLogin Successful! Welcome %s\n", currentUser);
        mainMenu();
    } else {
        printf("\nAccess Denied.\n");
    }
    return 0;
}

void userpwdcheck() {
    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        fp = fopen(CREDENTIAL_FILE, "w");
        if (fp) {
            fprintf(fp, "admin admin123 ADMIN\n");
            fprintf(fp, "staff staff123 STAFF\n");
            fprintf(fp, "user user123 USER\n");
            printf("[System] usersinfo updated and default will be user\n");
            fclose(fp);
        }
    } else {
        fclose(fp);
    }
}

int loginSystem() {
    char username[50], password[50];
    char fileUser[50], filePass[50], fileRole[10];
    printf("\n======= Login =======\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        printf("Error: %s not found\n", CREDENTIAL_FILE);
        return 0;
    }
    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            strcpy(currentRole, fileRole);
            strcpy(currentUser, fileUser);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void mainMenu() {
    if (strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if (strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else
        userMenu();
}

void adminMenu() {
    int choice;
    do {
        printf("\nAdmin Menu\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Delete ALL Students\n");
        printf("7. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: deleteAllStudents(); break;
            case 7: printf("Logging out...\n"); return;
            default: printf("Invalid choice\n");
        }
    } while(1);
}

void staffMenu() {
    int choice;
    do {
        printf("\nStaff Menu\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: printf("Logging out...\n"); return;
            default: printf("Invalid choice\n");
        }
    } while(1);
}

void userMenu() {
    int choice;
    do {
        printf("\nUser Menu\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: printf("Logging out...\n"); return;
            default: printf("Invalid choice\n");
        }
    } while(1);
}

void addStudent() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }
    printf("\n--- Add Student ---\n");
    printf("Enter Roll: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);
    fprintf(fp, "%d %s %f\n", s.roll, s.name, s.marks);
    fclose(fp);
    printf("Student added.\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("\nNo records.\n");
        return;
    }
    printf("\n");
    printf("Roll\tName\t\tMarks\n");
    printf("------------------------------\n");
    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        printf("%d\t%s\t%f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

void searchStudent() {
    struct Student s;
    int targetRoll;
    int found = 0;
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("\nNo records.\n");
        return;
    }
    printf("Enter Roll to search: ");
    scanf("%d", &targetRoll);
    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == targetRoll) {
            printf("\nRecord found.\n");
            printf("Roll: %d\tName: %s\tMarks: %f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) printf("Not found.\n");
    fclose(fp);
}

void updateStudent() {
    struct Student s;
    int targetRoll;
    int found = 0;
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) return;
    printf("Enter Roll to Update: ");
    scanf("%d", &targetRoll);
    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == targetRoll) {
            found = 1;
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(temp, "%d %s %f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
    fclose(temp);
    if (found) {
        remove(STUDENT_FILE);
        rename("temp.txt", STUDENT_FILE);
        printf("Updated.\n");
    } else {
        remove("temp.txt");
        printf("Not found.\n");
    }
}

void deleteStudent() {
    struct Student s;
    int targetRoll;
    int found = 0;
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) return;
    printf("Enter Roll to Delete: ");
    scanf("%d", &targetRoll);
    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == targetRoll) {
            found = 1;
        } else {
            fprintf(temp, "%d %s %f\n", s.roll, s.name, s.marks);
        }
    }
    fclose(fp);
    fclose(temp);
    if (found) {
        remove(STUDENT_FILE);
        rename("temp.txt", STUDENT_FILE);
        printf("Deleted.\n");
    } else {
        remove("temp.txt");
        printf("Not found.\n");
    }
}

void deleteAllStudents() {
    FILE *fp = fopen(STUDENT_FILE, "w");
    if (fp) {
        fclose(fp);
        printf("\nAll records deleted successfully.\n");
    } else {
        printf("\nError clearing file.\n");
    }
}
