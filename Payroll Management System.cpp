// Group 6 and 20: Payroll Management System

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    int age;
    char address[100];
    char phone[15];
    float salaryRatePerDay;
    int overtimeHours;
    int absences;
    float grossPay;
};

void displayMenu();
void calculateMonthlySalary();
void addNewEmployee();
void updateEmployeeInfo();
void searchEmployeeById();
void deleteEmployee();
void displayPayslip();
void displayEmployeeData();
int getNewEmployeeId();

int main() {
    FILE *employeeFile = fopen("employee_data.txt", "a+");

    if (employeeFile == NULL) {
        printf("Error opening or creating the employee_data.txt file.\n");
        return 1;
    }

    displayEmployeeData();

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("");

        switch (choice) {
            case 1:
                calculateMonthlySalary();
                break;
            case 2:
                addNewEmployee();
                break;
            case 3:
                updateEmployeeInfo();
                break;
            case 4:
                searchEmployeeById();
                break;
            case 5:
                deleteEmployee();
                break;
            case 6:
                displayPayslip();
                break;
            case 7:
                exit(0);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 7);

    fclose(employeeFile);
    return 0;
}

void displayMenu() {
    printf("\n--- Payroll Management System Menu ---\n");
    printf("1 - Calculate Monthly Salary\n");
    printf("2 - Add New Employee\n");
    printf("3 - Update Employee Information\n");
    printf("4 - Search for Employee via ID\n");
    printf("5 - Delete Employee\n");
    printf("6 - Print/Display Payslip\n");
    printf("7 - Exit\n");
}

void calculateMonthlySalary() {
    printf("Option 1 - Calculate Monthly Salary\n");

    int employeeId;
    printf("Enter the ID of the employee: ");
    scanf("%d", &employeeId);

    FILE *employeeFile = fopen("employee_data.txt", "r");
    if (employeeFile == NULL) {
        printf("Error opening the employee_data.txt file for searching.\n");
        return;
    }

    struct Employee emp;
    int found = 0;

    while (fscanf(employeeFile, "%d %s %d %s %s %f",
                  &emp.id, emp.name, &emp.age,
                  emp.address, emp.phone, &emp.salaryRatePerDay) != EOF) {
        if (emp.id == employeeId) {
            found = 1;

            int overtimeHours;
            printf("Enter overtime hours: ");
            scanf("%d", &overtimeHours);

            int absences;
            printf("Enter number of absences: ");
            scanf("%d", &absences);

            float monthlySalary = (emp.salaryRatePerDay * 30) + (overtimeHours * (emp.salaryRatePerDay / 8 * 1.5)) - (absences * emp.salaryRatePerDay);

            printf("Monthly Salary for Employee ID %d - %s: %.2f\n", emp.id, emp.name, monthlySalary);
            break;
        }
    }

    fclose(employeeFile);

    if (!found) {
        printf("Employee with ID %d not found.\n", employeeId);
    }
}

void addNewEmployee() {
    printf("Option 2 - Add New Employee\n");

    FILE *employeeFile = fopen("employee_data.txt", "a+");
    if (employeeFile == NULL) {
        printf("Error opening the employee_data.txt file for writing.\n");
        return;
    }

    struct Employee newEmployee;
    printf("Enter employee name: ");
    scanf("%s", newEmployee.name);
    printf("Enter employee age: ");
    scanf("%d", &newEmployee.age);
    printf("Enter employee address: ");
    scanf("%s", newEmployee.address);
    printf("Enter employee phone number: ");
    scanf("%s", newEmployee.phone);
    printf("Enter employee salary rate per day: ");
    scanf("%f", &newEmployee.salaryRatePerDay);

    newEmployee.id = getNewEmployeeId();

    fprintf(employeeFile, "%d %s %d %s %s %.2f\n",
            newEmployee.id, newEmployee.name, newEmployee.age,
            newEmployee.address, newEmployee.phone, newEmployee.salaryRatePerDay);

    fclose(employeeFile);

    printf("Employee added successfully!\n");
}

int getNewEmployeeId() {
    FILE *employeeFile = fopen("employee_data.txt", "r");
    if (employeeFile == NULL) {
        printf("Error opening the employee_data.txt file for reading.\n");
        return -1;
    }

    struct Employee emp;
    int maxId = 0;

    while (fscanf(employeeFile, "%d %s %d %s %s %f",
                  &emp.id, emp.name, &emp.age,
                  emp.address, emp.phone, &emp.salaryRatePerDay) != EOF) {
        if (emp.id > maxId) {
            maxId = emp.id;
        }
    }

    fclose(employeeFile);

    return maxId + 1;
}

void updateEmployeeInfo() {
    printf("Option 3 - Update Employee Information\n");

    int searchId;
    printf("Enter the ID of the employee to update: ");
    scanf("%d", &searchId);

    FILE *employeeFile = fopen("employee_data.txt", "r");
    if (employeeFile == NULL) {
        printf("Error opening the employee_data.txt file for updating.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening the temp.txt file for writing.\n");
        fclose(employeeFile);
        return;
    }

    struct Employee emp;

    int found = 0;
    while (fscanf(employeeFile, "%d %s %d %s %s %f",
                  &emp.id, emp.name, &emp.age,
                  emp.address, emp.phone, &emp.salaryRatePerDay) != EOF) {
        if (emp.id == searchId) {
            found = 1;
            // Display the current details for reference
            printf("Current Employee Details:\n");
            printf("%-5s %-20s %-25s %-30s %-15s %-10s\n", "ID", "Name", "Age", "Address", "Phone", "Salary Rate/Day");
            printf("%-5d %-20s %-25d %-30s %-15s %-10.2f\n", emp.id, emp.name, emp.age, emp.address, emp.phone, emp.salaryRatePerDay);

            // Update employee information
            printf("\nEnter new employee information:\n");
            printf("Enter employee name: ");
            scanf("%s", emp.name);
            printf("Enter employee age: ");
            scanf("%d", &emp.age);
            printf("Enter employee address: ");
            scanf("%s", emp.address);
            printf("Enter employee phone number: ");
            scanf("%s", emp.phone);
            printf("Enter employee salary rate per day: ");
            scanf("%f", &emp.salaryRatePerDay);

            fprintf(tempFile, "%d %s %d %s %s %.2f\n",
                    emp.id, emp.name, emp.age,
                    emp.address, emp.phone, emp.salaryRatePerDay);

            printf("Employee information updated successfully!\n");
        } else {
            fprintf(tempFile, "%d %s %d %s %s %.2f\n",
                    emp.id, emp.name, emp.age,
                    emp.address, emp.phone, emp.salaryRatePerDay);
        }
    }

    fclose(employeeFile);
    fclose(tempFile);

    remove("employee_data.txt");
    rename("temp.txt", "employee_data.txt");

    if (!found) {
        printf("Employee with ID %d not found.\n", searchId);
    }
}

void searchEmployeeById() {
    printf("Option 4 - Search for Employee via ID\n");

    FILE *employeeFile = fopen("employee_data.txt", "r");
    if (employeeFile == NULL) {
        printf("Error opening the employee_data.txt file for searching.\n");
        return;
    }

    struct Employee emp;
    int id;
    int found = 0;

    printf("\nList of ID Numbers and Names:               \n");
    printf("ID     %-45s \n", "Name");
    while (fscanf(employeeFile, "%d %s %d %s %s %f",
                &emp.id, emp.name, &emp.age,
                emp.address, emp.phone, &emp.salaryRatePerDay) != EOF) {
        printf("%-6d %-30s \n", emp.id, emp.name);
    }

    rewind(employeeFile);

    printf("\nEnter the ID of the employee to search: ");
    scanf("%d", &id);

    while (fscanf(employeeFile, "%d %s %d %s %s %f",
                &emp.id, emp.name, &emp.age,
                emp.address, emp.phone, &emp.salaryRatePerDay) != EOF) {
        if (emp.id == id) {
            found = 1;
            printf("%-5s %-20s %-25s %-30s %-15s %-10s\n", "ID", "Name", "Age", "Address", "Phone", "Salary Rate/Day");
            printf("%-5d %-20s %-25d %-30s %-15s %-10.2f\n", emp.id, emp.name, emp.age, emp.address, emp.phone, emp.salaryRatePerDay);
            break;
        }
    }

    fclose(employeeFile);

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
}

void deleteEmployee() {
    printf("Option 5 - Delete Employee\n");

    int deleteId;
    printf("Enter the ID of the employee to delete: ");
    scanf("%d", &deleteId);

    FILE *employeeFile = fopen("employee_data.txt", "r");
    if (employeeFile == NULL) {
        printf("Error opening the employee_data.txt file for searching.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening the temp.txt file for writing.\n");
        fclose(employeeFile);
        return;
    }

    struct Employee emp;
    int found = 0;

    while (fscanf(employeeFile, "%d %s %d %s %s %f",
                  &emp.id, emp.name, &emp.age,
                  emp.address, emp.phone, &emp.salaryRatePerDay) != EOF) {
        if (emp.id == deleteId) {
            found = 1;
            printf("Employee deleted successfully!\n");
        } else {
            fprintf(tempFile, "%d %s %d %s %s %.2f\n",
                    emp.id, emp.name, emp.age,
                    emp.address, emp.phone, emp.salaryRatePerDay);
        }
    }

    fclose(employeeFile);
    fclose(tempFile);

    remove("employee_data.txt");
    rename("temp.txt", "employee_data.txt");

    if (!found) {
        printf("Employee with ID %d not found.\n", deleteId);
    }
}

void displayPayslip() {
    printf("Option 6 - Display Payslip\n");

    int payslipId;
    printf("Enter the ID of the employee to generate payslip: ");
    scanf("%d", &payslipId);

    FILE *employeeFile = fopen("employee_data.txt", "r");
    if (employeeFile == NULL) {
        printf("Error opening the employee_data.txt file for searching.\n");
        return;
    }

    struct Employee emp;
    int found = 0;

    while (fscanf(employeeFile, "%d %s %d %s %s %f",
                  &emp.id, emp.name, &emp.age,
                  emp.address, emp.phone, &emp.salaryRatePerDay) != EOF) {
        if (emp.id == payslipId) {
            found = 1;
            float grossPay = emp.salaryRatePerDay * 30;

            printf("\nPayslip for Employee ID %d - %s:\n", emp.id, emp.name);
            printf("Gross Pay: %.2f\n", grossPay);
            break;
        }
    }

    fclose(employeeFile);

    if (!found) {
        printf("Employee with ID %d not found.\n", payslipId);
    }
}

void displayEmployeeData() {
    printf("Employee Data:\n");
    printf("%-5s %-20s %-25s %-30s %-15s %-10s\n", "ID", "Name", "Age", "Address", "Phone", "Salary Rate/Day");

    FILE *employeeFile = fopen("employee_data.txt", "r");
    if (employeeFile == NULL) {
        printf("Error opening the employee_data.txt file for reading.\n");
        return;
    }

    struct Employee emp;

    while (fscanf(employeeFile, "%d %s %d %s %s %f",
                  &emp.id, emp.name, &emp.age,
                  emp.address, emp.phone, &emp.salaryRatePerDay) != EOF) {
        printf("%-5d %-20s %-25d %-30s %-15s %-10.2f\n",
               emp.id, emp.name, emp.age, emp.address, emp.phone, emp.salaryRatePerDay);
    }

    fclose(employeeFile);
}