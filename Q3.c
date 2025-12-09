#include <stdio.h>
#include <string.h>

// Structure to store employee details
struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

// Function to display all employees
void displayEmployees(struct Employee emp[], int n) {
    printf("\n--- Employee Records ---\n");
    printf("ID\tName\t\tDesignation\tSalary\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t\t%s\t\t%.2f\n",
               emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
    }
}

// Function to find highest salary employee
void findHighestSalary(struct Employee emp[], int n) {
    int maxIndex = 0;

    for (int i = 1; i < n; i++) {
        if (emp[i].salary > emp[maxIndex].salary) {
            maxIndex = i;
        }
    }

    printf("\n--- Employee With Highest Salary ---\n");
    printf("ID: %d\n", emp[maxIndex].id);
    printf("Name: %s\n", emp[maxIndex].name);
    printf("Designation: %s\n", emp[maxIndex].designation);
    printf("Salary: %.2f\n", emp[maxIndex].salary);
}

// Function to search employee by ID or Name
void searchEmployee(struct Employee emp[], int n) {
    int choice, idSearch;
    char nameSearch[50];

    printf("\nSearch By:\n1. ID\n2. Name\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter Employee ID: ");
        scanf("%d", &idSearch);

        for (int i = 0; i < n; i++) {
            if (emp[i].id == idSearch) {
                printf("\n--- Employee Found ---\n");
                printf("ID: %d\n", emp[i].id);
                printf("Name: %s\n", emp[i].name);
                printf("Designation: %s\n", emp[i].designation);
                printf("Salary: %.2f\n", emp[i].salary);
                return;
            }
        }
        printf("Employee Not Found!\n");
    }

    else if (choice == 2) {
        printf("Enter Name: ");
        scanf("%s", nameSearch);

        for (int i = 0; i < n; i++) {
            if (strcmp(emp[i].name, nameSearch) == 0) {
                printf("\n--- Employee Found ---\n");
                printf("ID: %d\n", emp[i].id);
                printf("Name: %s\n", emp[i].name);
                printf("Designation: %s\n", emp[i].designation);
                printf("Salary: %.2f\n", emp[i].salary);
                return;
            }
        }
        printf("Employee Not Found!\n");
    }
}

// Function to update salary (pass by reference)
void updateLowSalaries(struct Employee emp[], int n, float threshold) {
    for (int i = 0; i < n; i++) {
        if (emp[i].salary < threshold) {
            emp[i].salary = emp[i].salary + (emp[i].salary * 0.10);  // 10% bonus
        }
    }
}

int main() {
    int n;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee emp[n];

    // Input Records
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &emp[i].id);

        printf("Name: ");
        scanf("%s", emp[i].name);

        printf("Designation: ");
        scanf("%s", emp[i].designation);

        printf("Salary: ");
        scanf("%f", &emp[i].salary);
    }

    displayEmployees(emp, n);
    findHighestSalary(emp, n);
    searchEmployee(emp, n);

    // Salary update example
    updateLowSalaries(emp, n, 50000);

    printf("\n--- After Salary Update (Below 50000 gets 10% bonus) ---\n");
    displayEmployees(emp, n);

    return 0;
}
